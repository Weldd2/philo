/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:50:06 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/14 20:36:36 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status_change_message(t_philo *philo, const char *message, t_msg_type type)
{
	if (lock_check(philo, &philo->data->msg_lock, \
"status_change_message") != 0)
		return (1);
	if (!gameover(philo))
	{
		print_message(philo, message);
		if (type == DEAD)
			set_dead(philo);
	}
	pthread_mutex_unlock(&philo->data->msg_lock);
	return (0);
}

void	print_message(t_philo *philo, const char *message)
{
	uintmax_t	current_time;

	current_time = retrieve_time_since_ms(philo->data->program_start_ms);
	printf("%lu %d %s\n", current_time, philo->seat, message);
}

int	print_error(t_error err)
{
	if (err == ERR_DATA)
		fprintf(stderr, "Usage: ./philo <number_of_philosophers> <time_to_die> "\
"<time_to_eat> <time_to_sleep> "\
"[number_of_times_each_philosopher_must_eat (optional)]\n"\
"All values must be strictly positive.\n");
	else
		fprintf(stderr, "Error: Something went wrong.\n");
	return (1);
}
