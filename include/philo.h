/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:27:16 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:56:29 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "mgc.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include "bitmask.h"

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	bool		stop_flag;
	pthread_t	*philo;
	pthread_t	reaper;
	ssize_t		*philo_meal_count;
	long long	*philo_last_meal;
	ssize_t		nb_philo;
	ssize_t		time_to_die;
	ssize_t		time_to_sleep;
	ssize_t		time_to_eat;
	ssize_t		must_eat;
	t_mutex		*mphilo_meal_count;
	t_mutex		*mphilo_meal_time;
	t_mutex		*forks;
	t_mutex		mprint;
	t_mutex		mstop;
}	t_data;

typedef struct s_philo_args
{
	t_data	*data;
	int		index;
}	t_philo_args;

void		start_threads(t_mgc *mgc, t_data *data);
void		simulation_single(t_data *data);
void		mutex_destroy(t_data *data);
bool		init_mutex(t_mgc *mgc, t_data *data);
void		*philo_single_lifecycle(void *void_data);
t_data		*init_data(t_mgc *mgc);
void		ft_usleep(int ms);
long long	timestamp(void);
void		die(t_data *data, int index);
int			is_int(char *arg, ssize_t *result);
void		*philo_lifecycle(void *arg);
bool		handle_args(int argc, char **argv, t_data *data);
long		ft_atoi(const char *nptr);
void		philo_eat(t_data *data, int index);
void		thread_print(t_data *data, int index, char *msg);
void		philo_sleep(t_data *data, int index);
void		ft_error(t_mgc *mgc, char *error_msg);
void		*reaper(void *void_data);
bool		is_dead(t_data *data);
ssize_t		get_philo_meal_count(t_data *data, int index);
void		set_philo_meal_count(t_data *data, int index, ssize_t value);
long long	get_philo_meal_time(t_data *data, int index);
void		set_philo_meal_time(t_data *data, int index, long long value);
void		stop_threads(t_data *data);

#endif
