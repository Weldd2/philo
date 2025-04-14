/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by improved          #+#    #+#             */
/*   Updated: 2025/04/14 20:36:20 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_forks(t_philo *philo)
{
	int	side;

	if (philo->seat % 2 == 0)
		side = LEFT;
	else
		side = RIGHT;
	if (lock_check(philo, philo->p_forks[side], "philo_take_forks") != 0)
		return (1);
	status_change_message(philo, MSG_FORK, FORK);
	if (lock_check(philo, philo->p_forks[!side], "philo_take_forks") != 0)
	{
		pthread_mutex_unlock(philo->p_forks[side]);
		return (1);
	}
	status_change_message(philo, MSG_FORK, FORK);
	return (0);
}

void	philo_clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->p_forks[LEFT]);
	pthread_mutex_unlock(philo->p_forks[RIGHT]);
}

int	philo_eat(t_philo *philo)
{
	if (update_eat_time(philo))
		return (1);
	status_change_message(philo, MSG_EAT, EAT);
	u_sleep_better(philo->data->msec_to_eat * 1000);
	if (lock_check(philo, &philo->eat_lock, "philo_eat") != 0)
		return (1);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat_lock);
	philo_clean_forks(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (status_change_message(philo, MSG_SLEEP, SLEEP))
		return (1);
	u_sleep_better(philo->data->msec_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (status_change_message(philo, MSG_THINK, THINK))
		return (1);
	return (0);
}
