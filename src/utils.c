/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:00:00 by improved          #+#    #+#             */
/*   Updated: 2025/04/14 17:50:21 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uintmax_t	retrieve_time_since_ms(uintmax_t start)
{
	struct timeval	time;
	uintmax_t		time_msec;

	gettimeofday(&time, NULL);
	time_msec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (time_msec < start)
		return (0);
	return (time_msec - start);
}

uintmax_t	retrieve_time_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void	u_sleep_better(uintmax_t usec)
{
	uintmax_t	start;

	start = retrieve_time_us();
	while (retrieve_time_us() - start < usec)
		usleep(100);
}

int	lock_check(t_philo *philo, pthread_mutex_t *lock, const char *fn)
{
	if (pthread_mutex_lock(lock) != 0)
	{
		printf("philo [%d] | FAILED to lock in %s\n", philo->seat, fn);
		return (1);
	}
	return (0);
}

int	update_eat_time(t_philo *philo)
{
	if (lock_check(philo, &philo->eat_lock, "update_eat_time") != 0)
		return (1);
	philo->last_ate_msec = retrieve_time_since_ms(0);
	philo->deadline = philo->last_ate_msec + philo->setup->msec_to_die;
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}
