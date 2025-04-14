/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/14 23:29:19 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_death(t_philo *philo)
{
	status_change_message(philo, MSG_DEAD, DEAD);
	return (NULL);
}

void	*handle_full_philo(t_philo *philo)
{
	if (lock_check(philo, &philo->data->dead_lock, "handle_full_philo") != 0)
		return ((void *)1);
	philo->data->full_philos++;
	if (philo->data->full_philos >= philo->data->num_philo)
	{
		philo->data->someone_dead = true;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (NULL);
}

bool	gameover(t_philo *philo)
{
	bool	result;

	if (lock_check(philo, &philo->data->dead_lock, "gameover") != 0)
		return (true);
	result = philo->data->someone_dead;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (result);
}

bool	has_eaten_enough(t_philo *philo)
{
	bool	result;

	if (philo->data->must_eat <= 0)
		return (false);
	if (lock_check(philo, &philo->eat_lock, "has_eaten_enough") != 0)
		return (false);
	result = (philo->times_eaten >= philo->data->must_eat);
	pthread_mutex_unlock(&philo->eat_lock);
	return (result);
}

void	set_dead(t_philo *philo)
{
	if (lock_check(philo, &philo->data->dead_lock, "set_dead") != 0)
		return ;
	philo->data->someone_dead = true;
	pthread_mutex_unlock(&philo->data->dead_lock);
}
