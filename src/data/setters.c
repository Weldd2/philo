/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:48:18 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 13:25:14 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo_meal_time(t_data *data, int index, long long value)
{
	pthread_mutex_lock(&data->philo_last_meal_mutex[index]);
	data->philo_last_meal[index] = value;
	pthread_mutex_unlock(&data->philo_last_meal_mutex[index]);
}

void	increment_philo_meal_count(t_data *data, int index)
{
	pthread_mutex_lock(&data->philo_meal_count_mutex[index]);
	data->philo_meal_count[index]++;
	pthread_mutex_unlock(&data->philo_meal_count_mutex[index]);
}
