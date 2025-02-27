/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:54 by antoinemura       #+#    #+#             */
/*   Updated: 2025/02/27 12:18:39 by antoinemura      ###   ########.fr       */
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
		pthread_mutex_lock(&data->stop_mutex);
		if (data->must_eat >= i)
			data->stop_flag = true;
		if (data->stop_flag == true)
			break ;
		pthread_mutex_unlock(&data->stop_mutex);
		philo_eat(data, philo_args->index);
		i++;
		philo_sleep(data, philo_args->index);
		philo_think(data, philo_args->index);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (NULL);
}
