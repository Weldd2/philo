/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:54 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 11:52:12 by antoinemura      ###   ########.fr       */
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
	stop_threads(data);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms(), index, "died");
	fflush(stdout);
	pthread_mutex_unlock(&data->print_mutex);
	EX("%d died, death detection time : %lld", index, (get_time_in_ms() - data->philo_last_meal[index]) - data->time_to_die);
}

bool	is_dead(t_data *data)
{
	bool	r;

	if (!data)
		return (false);
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

	if (!arg)
		exit(EXIT_FAILURE);
	philo_args = (t_philo_args*)arg;
	data = philo_args->data;
	index = philo_args->index;	
	while (!is_dead(data))
	{
		philo_eat(data, index);
		pthread_mutex_lock(&data->philo_meal_count_mutex[index]);
		data->philo_meal_count[index]++;
		pthread_mutex_unlock(&data->philo_meal_count_mutex[index]);
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

	if (!void_data)
		return (false);
	data = (t_data *)void_data;
	index = 0;
	mask = bitmask_create(data->nb_philo);
	while (1)
	{
		usleep(2000);
		pthread_mutex_lock(&data->philo_last_meal_mutex[index]);
		if ((get_time_in_ms() - data->philo_last_meal[index]) >= data->time_to_die)
			die(data, index);
		pthread_mutex_unlock(&data->philo_last_meal_mutex[index]);
		if (data->must_eat != 0)
		{
			pthread_mutex_lock(&data->philo_meal_count_mutex[index]);
			if (data->philo_meal_count[index] >= data->must_eat)
				bitmask_set(mask, index);
			pthread_mutex_unlock(&data->philo_meal_count_mutex[index]);
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
