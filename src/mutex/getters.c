/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:48:18 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:15:32 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_philo_meal_time(t_data *data, int index)
{
	long long	result;

	pthread_mutex_lock(&data->mphilo_meal_time[index]);
	result = data->philo_last_meal[index];
	pthread_mutex_unlock(&data->mphilo_meal_time[index]);
	return (result);
}

ssize_t	get_philo_meal_count(t_data *data, int index)
{
	ssize_t	result;

	pthread_mutex_lock(&data->mphilo_meal_count[index]);
	result = data->philo_meal_count[index];
	pthread_mutex_unlock(&data->mphilo_meal_count[index]);
	return (result);
}
