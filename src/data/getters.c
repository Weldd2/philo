/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:48:18 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 13:00:34 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_philo_meal_time(t_data *data, int index)
{
	long long	result;

	pthread_mutex_lock(&data->philo_last_meal_mutex[index]);
	result = data->philo_last_meal[index];
	pthread_mutex_unlock(&data->philo_last_meal_mutex[index]);
	return (result);
}

ssize_t	get_philo_meal_count(t_data *data, int index)
{
	ssize_t	result;

	pthread_mutex_lock(&data->philo_meal_count_mutex[index]);
	result = data->philo_meal_count[index];
	pthread_mutex_unlock(&data->philo_meal_count_mutex[index]);
	return (result);
}
