/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:19:21 by antoinemura       #+#    #+#             */
/*   Updated: 2025/02/27 16:56:14 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

t_data	*init_data(t_mgc *mgc)
{
	t_data	*data;

	data = mgc_create_block(mgc, sizeof(t_data), 1);
	if (!data)
		ft_error(mgc, "data allocation :");
	data->forks = NULL;
	data->philo_last_meal = NULL;
	data->philo = NULL;
	data->stop_flag = NULL;
	data->stop_mutex = NULL;
	data->nb_philo = 0;
	data->time_to_die = 0;
	data->time_to_sleep = 0;
	data->time_to_eat = 0;
	data->must_eat = 0;
	data->forks = NULL;
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		ft_error(mgc, "print mutex");
	return (data);
}

bool	init_mutex(t_mgc *mgc, t_data *data)
{
	ssize_t	index;
	index = 0;
	data->forks = mgc_create_block(mgc, sizeof(pthread_mutex_t), data->nb_philo);
	data->philo_last_meal_mutex = mgc_create_block(mgc, sizeof(pthread_mutex_t), data->nb_philo);
	data->stop_mutex = mgc_create_block(mgc, sizeof(pthread_mutex_t), data->nb_philo);
	data->stop_flag = mgc_create_block(mgc, sizeof(bool), data->nb_philo);
	while (index < data->nb_philo)
	{
		data->stop_flag[index] = false;
		if (pthread_mutex_init(&(data->stop_mutex[index]), NULL) != 0)
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
	data->philo = mgc_create_block(mgc, sizeof(pthread_t), data->nb_philo);
	data->philo_last_meal = mgc_create_block(mgc, sizeof(long long), data->nb_philo);
	if (!data->philo)
		exit(EXIT_FAILURE);
	while (index < data->nb_philo)
	{
		philo_args[index].data = data;
		philo_args[index].index = index;
		if (pthread_create(&(data->philo[index]), NULL, philo_lifecycle, &philo_args[index])  != 0)
			exit(EXIT_FAILURE);
		index++;
	}
}

void	terminate(t_mgc *mgc, t_data *data)
{
	ssize_t	index;

	index = 0;
	while (index < data->nb_philo)
	{
		pthread_join(data->philo[index], NULL);
		pthread_mutex_destroy(&(data->forks[index]));
		pthread_mutex_destroy(&(data->stop_mutex[index]));
		index++;
	}
	pthread_mutex_destroy(&(data->print_mutex));
	mgc_free(mgc);
}

bool	reaper(__attribute__((unused)) t_mgc *mgc, t_data *data)
{
	ssize_t	index;
	
	index = 0;
	while (index < data->nb_philo)
	{
		pthread_mutex_lock(&data->philo_last_meal_mutex[index]);
		if (get_time_in_ms() - data->philo_last_meal[index] > data->time_to_die)
		{
			thread_print(data, index, "died");
			pthread_mutex_lock(&data->stop_mutex[index]);
			data->stop_flag[index] = true;
			pthread_mutex_unlock(&data->stop_mutex[index]);
		}
		pthread_mutex_unlock(&data->philo_last_meal_mutex[index]);
		index++;
	}
	return (true);
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

// all data needed
// philo nb
// philo list
// forks list
// stop mutex
// stop flag
// time etc
// must eat flag

// lifetime use :
// index
// mutex print, flag
// fork right, fork left
// time die, time sleep, time eat, must eat