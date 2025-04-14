/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by improved          #+#    #+#             */
/*   Updated: 2025/04/14 17:45:35 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_setup	setup;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
		return (print_error(ERR_SETUP));
	init_setup(&setup);
	if (init_setup_and_philos(&setup, &philos, av))
		return (clean_exit(&setup, NULL));
	if (start_philo_threads(&setup, philos))
		return (print_error(ERR_GEN) | clean_exit(&setup, &philos));
	clean_exit(&setup, &philos);
	return (0);
}

int	init_setup_and_philos(t_setup *setup, t_philo **philos, char **av)
{
	if (parse_args_into_setup(setup, (const char **)(av + 1)))
	{
		print_error(ERR_SETUP);
		return (1);
	}
	if (init_forks(setup))
	{
		print_error(ERR_GEN);
		return (1);
	}
	if (init_philos(setup, philos))
	{
		print_error(ERR_GEN);
		return (1);
	}
	return (0);
}

int	start_philo_threads(t_setup *setup, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < setup->num_philo)
	{
		if (pthread_create(&philos[i].id, NULL, &philo_do, &philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < setup->num_philo)
	{
		if (pthread_join(philos[i].id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	clean_exit(t_setup *setup, t_philo **philos)
{
	int	i;

	if (setup->initialized.fork_init)
	{
		i = 0;
		while (i < setup->num_philo)
		{
			pthread_mutex_destroy(&setup->forks[i]);
			i++;
		}
		free(setup->forks);
	}
	if (philos && setup->initialized.philos_init)
	{
		i = 0;
		while (i < setup->num_philo)
		{
			pthread_mutex_destroy(&(*philos)[i].eat_lock);
			i++;
		}
		free(*philos);
		*philos = NULL;
	}
	pthread_mutex_destroy(&setup->msg_lock);
	return (pthread_mutex_destroy(&setup->dead_lock), 1);
}
