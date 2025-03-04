/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:19:21 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:34:57 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(t_mgc *mgc)
{
	t_data	*data;

	data = mgc_alloc(mgc, sizeof(t_data), 1);
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
	return (data);
}

void	data_allocate(t_mgc *mgc, t_data *data)
{
	ssize_t			index;

	index = 0;
	if (!data)
		ft_error(mgc, "allocation failed");
	data->philo = mgc_alloc(mgc, sizeof(pthread_t), data->nb_philo + 1);
	data->philo_last_meal = mgc_alloc(mgc, sizeof(long long), data->nb_philo);
	data->philo_meal_count = mgc_alloc(mgc, sizeof(ssize_t), data->nb_philo);
	if (!data->philo || !data->philo_last_meal || !data->philo_meal_count)
		ft_error(mgc, "allocation failed");
	while (index < data->nb_philo)
	{
		data->philo_meal_count[index] = 0;
		data->philo_last_meal[index] = timestamp();
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
		index++;
	}
	pthread_join(data->reaper, NULL);
	mutex_destroy(data);
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
	data_allocate(mgc, data);
	if (data->nb_philo == 1)
		simulation_single(data);
	else
		start_threads(mgc, data);
	terminate(mgc, data);
	return (0);
}
