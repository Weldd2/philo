/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:09:24 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:55:17 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_data *data)
{
	bool	r;

	pthread_mutex_lock(&data->mstop);
	r = data->stop_flag;
	pthread_mutex_unlock(&data->mstop);
	return (r);
}

void	stop_threads(t_data *data)
{
	pthread_mutex_lock(&data->mstop);
	data->stop_flag = true;
	pthread_mutex_unlock(&data->mstop);
}

void	die(t_data *data, int index)
{
	long long	time;

	time = timestamp();
	stop_threads(data);
	pthread_mutex_lock(&data->mprint);
	printf("%lld %d %s\n", time, index, "died");
	pthread_mutex_unlock(&data->mprint);
}

void	start_threads(t_mgc *mgc, t_data *data)
{
	t_philo_args	*philo_args;
	ssize_t			index;

	index = 0;
	philo_args = mgc_alloc(mgc, sizeof(t_philo_args), data->nb_philo);
	if (!philo_args)
		exit(EXIT_FAILURE);
	while (index < data->nb_philo)
	{
		philo_args[index].data = data;
		philo_args[index].index = index;
		if (pthread_create(&(data->philo[index]), NULL, philo_lifecycle, \
			&philo_args[index]) != 0)
			exit(EXIT_FAILURE);
		index++;
	}
	if (pthread_create(&(data->reaper), NULL, reaper, data) != 0)
		exit(EXIT_FAILURE);
}
