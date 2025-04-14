/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by improved          #+#    #+#             */
/*   Updated: 2025/04/14 17:28:09 by antoinemura      ###   ########.fr       */
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
	if (lock_check(philo, &philo->setup->dead_lock, "handle_full_philo") != 0)
		return ((void *)1);
	philo->setup->full_philos++;
	if (philo->setup->full_philos >= philo->setup->num_philo)
	{
		philo->setup->someone_dead = true;
		pthread_mutex_unlock(&philo->setup->dead_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->setup->dead_lock);
	return (NULL);
}

bool	gameover(t_philo *philo)
{
	bool	result;

	if (lock_check(philo, &philo->setup->dead_lock, "gameover") != 0)
		return (true);
	result = philo->setup->someone_dead;
	pthread_mutex_unlock(&philo->setup->dead_lock);
	return (result);
}

bool	has_eaten_enough(t_philo *philo)
{
	return (philo->setup->must_eat > 0
		&& philo->times_eaten >= philo->setup->must_eat);
}

void	set_dead(t_philo *philo)
{
	if (lock_check(philo, &philo->setup->dead_lock, "set_dead") != 0)
		return ;
	philo->setup->someone_dead = true;
	pthread_mutex_unlock(&philo->setup->dead_lock);
}
