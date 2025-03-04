/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:54 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:55:40 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_lifecycle(void *arg)
{
	t_philo_args	*philo_args;
	t_data			*data;
	int				index;
	ssize_t			meal_count;

	if (!arg)
		exit(EXIT_FAILURE);
	philo_args = (t_philo_args *)arg;
	data = philo_args->data;
	index = philo_args->index;
	meal_count = 0;
	while (!is_dead(data))
	{
		philo_eat(data, index);
		set_philo_meal_time(data, index, timestamp());
		meal_count++;
		if (meal_count >= data->must_eat)
			set_philo_meal_count(data, index, meal_count);
		philo_sleep(data, index);
		thread_print(data, index, "is thinking");
	}
	return (NULL);
}
