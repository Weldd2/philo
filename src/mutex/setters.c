/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:48:18 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:15:32 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo_meal_time(t_data *data, int index, long long value)
{
	pthread_mutex_lock(&data->mphilo_meal_time[index]);
	data->philo_last_meal[index] = value;
	pthread_mutex_unlock(&data->mphilo_meal_time[index]);
}

void	set_philo_meal_count(t_data *data, int index, ssize_t value)
{
	pthread_mutex_lock(&data->mphilo_meal_count[index]);
	data->philo_meal_count[index] = value;
	pthread_mutex_unlock(&data->mphilo_meal_count[index]);
}
