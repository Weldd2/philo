/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by improved          #+#    #+#             */
/*   Updated: 2025/04/14 19:08:39 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_setup(t_setup *setup)
{
	setup->num_philo = 0;
	setup->msec_to_die = 0;
	setup->msec_to_eat = 0;
	setup->msec_to_sleep = 0;
	setup->must_eat = 0;
	setup->full_philos = 0;
	setup->program_start_ms = retrieve_time_since_ms(0);
	setup->someone_dead = false;
	pthread_mutex_init(&setup->msg_lock, NULL);
	pthread_mutex_init(&setup->dead_lock, NULL);
	setup->initialized.fork_init = false;
	setup->initialized.philos_init = false;
}

int	parse_args_into_setup(t_setup *setup, const char **args)
{
	setup->num_philo = atoi(args[0]);
	setup->msec_to_die = atoi(args[1]);
	setup->msec_to_eat = atoi(args[2]);
	setup->msec_to_sleep = atoi(args[3]);
	if (args[4])
		setup->must_eat = atoi(args[4]);
	else
		setup->must_eat = 0;
	if (setup->num_philo <= 0 || setup->msec_to_die <= 0
		|| setup->msec_to_eat <= 0 || setup->msec_to_sleep <= 0
		|| (args[4] && setup->must_eat <= 0))
		return (1);
	return (0);
}

int	init_forks(t_setup *setup)
{
	int	i;

	i = 0;
	setup->forks = malloc(sizeof(t_mutex) * setup->num_philo);
	if (!setup->forks)
		return (1);
	while (i < setup->num_philo)
	{
		if (pthread_mutex_init(&(setup->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	setup->initialized.fork_init = true;
	return (0);
}

void	set_philo_mutexes(int i, t_philo *philo, t_mutex *forks,\
	t_mutex **p_forks)
{
	p_forks[LEFT] = &forks[i];
	p_forks[RIGHT] = &forks[(i + 1) % philo->setup->num_philo];
}

int	init_philos(t_setup *setup, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * setup->num_philo);
	if (!*philos)
		return (1);
	while (i < setup->num_philo)
	{
		(*philos)[i].id = 0;
		(*philos)[i].seat = i + 1;
		(*philos)[i].active = false;
		(*philos)[i].times_eaten = 0;
		(*philos)[i].last_ate_msec = retrieve_time_since_ms(0);
		(*philos)[i].deadline = (*philos)[i].last_ate_msec + setup->msec_to_die;
		(*philos)[i].setup = setup;
		if (pthread_mutex_init(&(*philos)[i].active_lock, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(*philos)[i].eat_lock, NULL) != 0)
			return (1);
		set_philo_mutexes(i, &(*philos)[i], setup->forks, (*philos)[i].p_forks);
		i++;
	}
	setup->initialized.philos_init = true;
	return (0);
}
