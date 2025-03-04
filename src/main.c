/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:19:21 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 15:20:09 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(t_mgc *mgc)
{
	t_data	*data;

	data = mgc_create_block(mgc, sizeof(t_data), 1);
	if (!data)
		ft_error(mgc, "data allocation :");
	data->forks = NULL;
	data->philo_last_meal = NULL;
	data->philo = NULL;
	data->stop_flag = false;
	data->philo_meal_count = NULL;
	data->nb_philo = 0;
	data->time_to_die = 0;
	data->time_to_sleep = 0;
	data->time_to_eat = 0;
	data->must_eat = 0;
	data->forks = NULL;
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		ft_error(mgc, "print mutex");
	if (pthread_mutex_init(&(data->stop_mutex), NULL) != 0)
		ft_error(mgc, "stop mutex");
	return (data);
}

bool	init_mutex(t_mgc *mgc, t_data *data)
{
	ssize_t	index;

	index = 0;
	data->forks = mgc_create_block(mgc, sizeof(pthread_mutex_t), data->nb_philo);
	data->philo_last_meal_mutex = mgc_create_block(mgc, sizeof(pthread_mutex_t), data->nb_philo);
	data->philo_meal_count = mgc_create_block(mgc, sizeof(ssize_t), data->nb_philo);
	data->philo_meal_count_mutex = mgc_create_block(mgc, sizeof(pthread_mutex_t), data->nb_philo);
	while (index < data->nb_philo)
	{
		data->philo_meal_count[index] = 0;
		data->stop_flag = false;
		if (pthread_mutex_init(&(data->philo_meal_count_mutex[index]), NULL) != 0)
			return (perror("pthread_mutex_init failed"), false);
		if (pthread_mutex_init(&(data->philo_last_meal_mutex[index]), NULL) != 0)
			return (perror("pthread_mutex_init failed"), false);
		if (pthread_mutex_init(&(data->forks[index]), NULL) != 0)
			return (perror("pthread_mutex_init failed"), false);
		index++;
	}
	return (true);
}

void	simulation(t_mgc *mgc, t_data *data)
{
	ssize_t			index;
	t_philo_args	*philo_args;

	index = 0;
	if (!data)
		exit(EXIT_FAILURE);
	philo_args = mgc_create_block(mgc, sizeof(t_philo_args), data->nb_philo);
	if (!philo_args)
		exit(EXIT_FAILURE);
	data->philo = mgc_create_block(mgc, sizeof(pthread_t), data->nb_philo + 1);
	data->philo_last_meal = mgc_create_block(mgc, sizeof(long long), data->nb_philo);
	if (!data->philo)
		exit(EXIT_FAILURE);
	while (index < data->nb_philo)
	{
		philo_args[index].data = data;
		philo_args[index].index = index;
		data->philo_last_meal[index] = timestamp();
		if (pthread_create(&(data->philo[index]), NULL, philo_lifecycle, &philo_args[index])  != 0)
			exit(EXIT_FAILURE);
		index++;
	}
	if (pthread_create(&(data->reaper), NULL, reaper, data)  != 0)
		exit(EXIT_FAILURE);
}

void	terminate(t_mgc *mgc, t_data *data)
{
	ssize_t	index;

	index = 0;
	while (index < data->nb_philo)
	{
		pthread_join(data->philo[index], NULL);
		index++;
	}
	pthread_join(data->reaper, NULL);
	pthread_mutex_destroy(&(data->print_mutex));
	index = 0;
	pthread_mutex_destroy(&(data->stop_mutex));
	while (index < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->forks[index]));
		index++;
	}
	mgc_free(mgc);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_mgc	*mgc;

	mgc = mgc_init();
	if (argc != 5 && argc != 6)
		ft_error(mgc, "Usage: ./philo <nb_philo> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [<philo meal goal>]\n"
			"Times are expressed in milliseconds.");
	data = init_data(mgc);
	if (!data)
		ft_error(mgc, "init data");
	if (!handle_args(argc, argv, data))
		ft_error(mgc, "All arguments must be integers strictly positive.");
	init_mutex(mgc, data);
	simulation(mgc, data);
	terminate(mgc, data);
	return (0);
}
