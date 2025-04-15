/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/14 23:29:19 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(t_philo *philo, t_thread tid)
{
	if (philo->data->num_philo == 1)
	{
		status_change_message(philo, MSG_FORK, FORK);
		u_sleep_better(philo->data->msec_to_die * 1000);
		pthread_mutex_lock(&philo->active_lock);
		philo->active = false;
		pthread_mutex_unlock(&philo->active_lock);
		status_change_message(philo, MSG_DEAD, DEAD);
		return (pthread_join(tid, NULL), NULL);
	}
	usleep((philo->seat % 2 == 0) * 1000);
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
	pthread_mutex_lock(&philo->active_lock);
	philo->active = false;
	pthread_mutex_unlock(&philo->active_lock);
	return (pthread_join(tid, NULL), NULL);
}

void	*philo_do(void *philo_arg)
{
	t_philo		*philo;
	t_thread	tid;

	philo = (t_philo *)philo_arg;
	pthread_mutex_lock(&philo->active_lock);
	philo->active = true;
	pthread_mutex_unlock(&philo->active_lock);
	if (pthread_create(&tid, NULL, &philo_check, philo_arg) != 0)
		return ((void *)1);
	return (philo_routine(philo, tid));
}

int	philo_check_conditions(t_philo *philo)
{
	uintmax_t	current_time;

	if (lock_check(philo, &philo->eat_lock, "philo_check") != 0)
		return (1);
	current_time = retrieve_time_since_ms(0);
	if (current_time > philo->deadline)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		handle_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	if (philo->data->must_eat > 0 && has_eaten_enough(philo))
	{
		handle_full_philo(philo);
		return (1);
	}
	return (0);
}

void	*philo_check(void *philo_arg)
{
	t_philo		*philo;
	bool		active;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		pthread_mutex_lock(&philo->active_lock);
		active = philo->active;
		pthread_mutex_unlock(&philo->active_lock);
		if (!active)
			break ;
		if (philo_check_conditions(philo) != 0)
			return ((void *)1);
		usleep(1000);
	}
	return (NULL);
}
