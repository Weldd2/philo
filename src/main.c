/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/14 23:29:19 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (print_error(ERR_DATA));
	init_data(&data);
	if (init_data_and_philos(&data, &philos, argv))
		return (clean_exit(&data, NULL));
	if (start_philo_threads(&data, philos))
		return (print_error(ERR_GEN), clean_exit(&data, &philos));
	clean_exit(&data, &philos);
	return (0);
}

int	init_data_and_philos(t_data *data, t_philo **philos, char **av)
{
	if (parse_args_into_data(data, (const char **)(av + 1)))
	{
		print_error(ERR_DATA);
		return (1);
	}
	if (init_forks(data))
	{
		print_error(ERR_GEN);
		return (1);
	}
	if (init_philos(data, philos))
	{
		print_error(ERR_GEN);
		return (1);
	}
	return (0);
}

int	start_philo_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&philos[i].id, NULL, &philo_do, &philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(philos[i].id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	clean_exit(t_data *data, t_philo **philos)
{
	int	i;

	if (data->initialized.fork_init)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (philos && data->initialized.philos_init)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&(*philos)[i].eat_lock);
			i++;
		}
		free(*philos);
		*philos = NULL;
	}
	pthread_mutex_destroy(&data->msg_lock);
	return (pthread_mutex_destroy(&data->dead_lock), 1);
}
