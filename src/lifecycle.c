/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by improved          #+#    #+#             */
/*   Updated: 2025/04/14 18:04:28 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(t_philo *philo, pthread_t tid)
{
	if (philo->setup->num_philo == 1)
	{
		status_change_message(philo, MSG_FORK, FORK);
		u_sleep_better(philo->setup->msec_to_die * 1000);
		philo->active = false;
		pthread_join(tid, NULL);
		return (NULL);
	}
	if (philo->seat % 2 == 0)
		usleep(1000);
	if (update_eat_time(philo) == 0)
	{
		while (!gameover(philo) && !has_eaten_enough(philo))
		{
			if (philo_take_forks(philo) || philo_eat(philo)
				|| philo_sleep(philo) || philo_think(philo))
				break ;
			usleep(500);
		}
	}
	philo->active = false;
	pthread_join(tid, NULL);
	return (NULL);
}

void	*philo_do(void *philo_arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philo_arg;
	philo->active = true;
	if (pthread_create(&tid, NULL, &philo_check, philo_arg) != 0)
		return ((void *)1);
	return (philo_routine(philo, tid));
}

void	*philo_check(void *philo_arg)
{
	t_philo		*philo;
	uintmax_t	current_time;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		if (!philo->active)
			break ;
		if (lock_check(philo, &philo->eat_lock, "philo_check") != 0)
			return ((void *)1);
		current_time = retrieve_time_since_ms(0);
		if (current_time > philo->deadline)
		{
			pthread_mutex_unlock(&philo->eat_lock);
			return (handle_death(philo));
		}
		pthread_mutex_unlock(&philo->eat_lock);
		if (philo->setup->must_eat > 0 && has_eaten_enough(philo))
			return (handle_full_philo(philo));
		usleep(1000);
	}
	return (NULL);
}
