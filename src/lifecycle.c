/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:54 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 15:34:48 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_threads(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = true;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	die(t_data *data, int index)
{
	long long	time;

	time = timestamp();
	stop_threads(data);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", time, index, "died");
	pthread_mutex_unlock(&data->print_mutex);
	EX("%d died, death detection time : %lld", index, (time - data->philo_last_meal[index]) - data->time_to_die);
}

bool	is_dead(t_data *data)
{
	bool	r;

	pthread_mutex_lock(&data->stop_mutex);
	r = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (r);
}

void	*philo_lifecycle(void *arg)
{
	t_philo_args	*philo_args;
	t_data			*data;
	int				index;
	ssize_t			meal_count;

	if (!arg)
		exit(EXIT_FAILURE);
	philo_args = (t_philo_args*)arg;
	data = philo_args->data;
	index = philo_args->index;
	meal_count = 0;
	while (!is_dead(data))
	{
		philo_eat(data, index);
		meal_count++;
		if (meal_count >= data->must_eat)
			set_philo_meal_count(data, index, meal_count);
		philo_sleep(data, index);
		thread_print(data, index, "is thinking");
	}
	return (NULL);
}

void	*reaper(void *void_data)
{
	t_data			*data;
	int				index;
	t_bitmask		*mask;
	bool			must_eat;

	if (!void_data)
		return (false);
	data = (t_data *)void_data;
	index = 0;
	must_eat = data->must_eat != 0;
	mask = bitmask_create(data->nb_philo);
	while (1)
	{
		ft_usleep(5);
		if ((timestamp() - get_philo_meal_time(data, index)) >= data->time_to_die)
			die(data, index);
		if (must_eat && (get_philo_meal_count(data, index) >= data->must_eat))
		{
			bitmask_set(mask, index);
			if (are_bitmask_all_set(mask))
				stop_threads(data);
		}
		if (is_dead(data))
			break ;
		index = (index + 1) % data->nb_philo;
	}
	bitmask_free(mask);
	return (NULL);
}
