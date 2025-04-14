/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/14 20:19:46 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	data->num_philo = 0;
	data->msec_to_die = 0;
	data->msec_to_eat = 0;
	data->msec_to_sleep = 0;
	data->must_eat = 0;
	data->full_philos = 0;
	data->program_start_ms = retrieve_time_since_ms(0);
	data->someone_dead = false;
	pthread_mutex_init(&data->msg_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	data->initialized.fork_init = false;
	data->initialized.philos_init = false;
}

int	parse_args_into_data(t_data *data, const char **args)
{
	data->num_philo = atoi(args[0]);
	data->msec_to_die = atoi(args[1]);
	data->msec_to_eat = atoi(args[2]);
	data->msec_to_sleep = atoi(args[3]);
	if (args[4])
		data->must_eat = atoi(args[4]);
	else
		data->must_eat = 0;
	if (data->num_philo <= 0 || data->msec_to_die <= 0
		|| data->msec_to_eat <= 0 || data->msec_to_sleep <= 0
		|| (args[4] && data->must_eat <= 0))
		return (1);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_mutex) * data->num_philo);
	if (!data->forks)
		return (1);
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	data->initialized.fork_init = true;
	return (0);
}

void	set_philo_mutexes(int i, t_philo *philo, t_mutex *forks, \
	t_mutex **p_forks)
{
	p_forks[LEFT] = &forks[i];
	p_forks[RIGHT] = &forks[(i + 1) % philo->data->num_philo];
}

int	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!*philos)
		return (1);
	while (i < data->num_philo)
	{
		(*philos)[i].id = 0;
		(*philos)[i].seat = i + 1;
		(*philos)[i].active = false;
		(*philos)[i].times_eaten = 0;
		(*philos)[i].last_ate_msec = retrieve_time_since_ms(0);
		(*philos)[i].deadline = (*philos)[i].last_ate_msec + data->msec_to_die;
		(*philos)[i].data = data;
		if (pthread_mutex_init(&(*philos)[i].active_lock, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(*philos)[i].eat_lock, NULL) != 0)
			return (1);
		set_philo_mutexes(i, &(*philos)[i], data->forks, (*philos)[i].p_forks);
		i++;
	}
	data->initialized.philos_init = true;
	return (0);
}
