/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:51:39 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:15:58 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(t_data *data)
{
	ssize_t	index;

	index = 0;
	pthread_mutex_destroy(&(data->mprint));
	pthread_mutex_destroy(&(data->mstop));
	while (index < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->forks[index]));
		pthread_mutex_destroy(&(data->mphilo_meal_count[index]));
		pthread_mutex_destroy(&(data->mphilo_meal_time[index]));
		index++;
	}
}
