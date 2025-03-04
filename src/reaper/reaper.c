/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:53:32 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:55:35 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_check(t_data *data, int index)
{
	if ((timestamp() - get_philo_meal_time(data, index)) >= data->time_to_die)
		die(data, index);
}

static void	meal_check(t_data *data, int index, bool must_eat, t_bitmask *mask)
{
	if (must_eat && (get_philo_meal_count(data, index) >= data->must_eat))
	{
		bitmask_set(mask, index);
		if (are_bitmask_all_set(mask))
			stop_threads(data);
	}
}

void	*reaper(void *void_data)
{
	t_data			*data;
	int				index;
	t_bitmask		*mask;
	bool			must_eat;

	if (!void_data)
		return (false);
	data = (t_data *)void_data;
	index = 0;
	must_eat = data->must_eat != 0;
	mask = bitmask_create(data->nb_philo);
	while (1)
	{
		ft_usleep(1);
		meal_check(data, index, must_eat, mask);
		time_check(data, index);
		if (is_dead(data))
			break ;
		index = (index + 1) % data->nb_philo;
	}
	bitmask_free(mask);
	return (NULL);
}
