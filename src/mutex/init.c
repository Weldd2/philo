/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:47:45 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:42:03 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_mutex(t_mgc *mgc, t_data *data)
{
	ssize_t	index;

	index = 0;
	data->forks = mgc_alloc(mgc, sizeof(t_mutex), data->nb_philo);
	data->mphilo_meal_time = mgc_alloc(mgc, sizeof(t_mutex), data->nb_philo);
	data->mphilo_meal_count = mgc_alloc(mgc, sizeof(t_mutex), data->nb_philo);
	if (pthread_mutex_init(&(data->mprint), NULL) != 0)
		ft_error(mgc, "print mutex");
	if (pthread_mutex_init(&(data->mstop), NULL) != 0)
		ft_error(mgc, "stop mutex");
	while (index < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->mphilo_meal_count[index]), NULL) != 0)
			return (perror("pthread_mutex_init failed"), false);
		if (pthread_mutex_init(&(data->mphilo_meal_time[index]), NULL) != 0)
			return (perror("pthread_mutex_init failed"), false);
		if (pthread_mutex_init(&(data->forks[index]), NULL) != 0)
			return (perror("pthread_mutex_init failed"), false);
		index++;
	}
	return (true);
}
