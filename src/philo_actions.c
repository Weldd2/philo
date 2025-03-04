/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:35:21 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:47:25 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_print(t_data *data, int index, char *msg)
{
	long long	time;

	time = timestamp();
	if (is_dead(data))
		return ;
	pthread_mutex_lock(&data->mprint);
	printf("%lld %d %s\n", time, index, msg);
	pthread_mutex_unlock(&data->mprint);
}

void	philo_eat(t_data *data, int index)
{
	int	fork1;
	int	fork2;

	fork1 = (index + (index % 2)) % data->nb_philo;
	fork2 = (index + ((index + 1) % 2)) % data->nb_philo;
	pthread_mutex_lock(&data->forks[fork1]);
	thread_print(data, index, "has taken a fork");
	pthread_mutex_lock(&data->forks[fork2]);
	thread_print(data, index, "has taken a fork");
	thread_print(data, index, "is eating");
	set_philo_meal_time(data, index, timestamp());
	ft_usleep(data->time_to_eat);
	set_philo_meal_time(data, index, timestamp());
	pthread_mutex_unlock(&data->forks[fork1]);
	pthread_mutex_unlock(&data->forks[fork2]);
}

void	philo_sleep(t_data *data, int index)
{
	thread_print(data, index, "is sleeping");
	ft_usleep(data->time_to_sleep);
}
