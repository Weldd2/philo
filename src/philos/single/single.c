/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:49:54 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:57:35 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_lifecycle(void *void_data)
{
	t_data	*data;

	data = (t_data *)void_data;
	pthread_mutex_lock(&data->forks[0]);
	thread_print(data, 0, "has taken a fork");
	ft_usleep(data->time_to_die);
	pthread_mutex_unlock(&data->forks[0]);
	return (NULL);
}

void	simulation_single(t_data *data)
{
	if (pthread_create(&(data->philo[0]), NULL, single_lifecycle, data) != 0)
		exit(EXIT_FAILURE);
	if (pthread_create(&(data->reaper), NULL, reaper, data) != 0)
		exit(EXIT_FAILURE);
}
