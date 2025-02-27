/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:54 by antoinemura       #+#    #+#             */
/*   Updated: 2025/02/27 17:00:32 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_lifecycle(void *arg)
{
	t_philo_args	*philo_args;
	int		i;

	if (!arg)
		exit(EXIT_FAILURE);
	philo_args = (t_philo_args*)arg;
	i = 0;
	t_data *data = philo_args->data;
	while (1)
	{
		pthread_mutex_lock(&data->stop_mutex[philo_args->index]);
		if ((data->must_eat != 0 && i >= data->must_eat) || data->stop_flag[philo_args->index])
		{
			thread_print(data, philo_args->index, "died");
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex[philo_args->index]);
		philo_eat(data, philo_args->index);
		i++;
		philo_sleep(data, philo_args->index);
		thread_print(data, philo_args->index, "is thinking");
	}
	pthread_mutex_unlock(&data->stop_mutex[philo_args->index]);
	return (NULL);
}
