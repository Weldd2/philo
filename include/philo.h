/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:08:11 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/14 20:31:10 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# define LEFT 0
# define RIGHT 1

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DEAD "died"

typedef enum e_msg_type
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_msg_type;

typedef enum e_error
{
	ERR_SETUP,
	ERR_GEN
}	t_error;

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_init
{
	bool	fork_init;
	bool	philos_init;
}	t_init;

typedef struct s_setup
{
	int				num_philo;
	int				msec_to_die;
	int				msec_to_eat;
	int				msec_to_sleep;
	int				must_eat;
	int				full_philos;
	uintmax_t		program_start_ms;
	bool			someone_dead;
	t_mutex			msg_lock;
	t_mutex			dead_lock;
	t_mutex			*forks;
	struct s_init	initialized;
}	t_setup;

typedef struct s_philo
{
	t_thread		id;
	int				seat;
	bool			active;
	t_mutex			active_lock;
	int				times_eaten;
	uintmax_t		last_ate_msec;
	uintmax_t		deadline;
	struct s_setup	*setup;
	t_mutex			eat_lock;
	t_mutex			*p_forks[2];
}	t_philo;

/* Main functions */
int			init_setup_and_philos(t_setup *setup, t_philo **philos, char **av);
int			start_philo_threads(t_setup *setup, t_philo *philos);
int			clean_exit(t_setup *setup, t_philo **philos);

/* Setup and initialization */
void		init_setup(t_setup *setup);
int			parse_args_into_setup(t_setup *setup, const char **args);
int			init_forks(t_setup *setup);
int			init_philos(t_setup *setup, t_philo **philos);
void		set_philo_mutexes(int i, t_philo *philo, t_mutex *forks, \
		t_mutex **p_forks);

/* Philosopher lifecycle */
void		*philo_do(void *philo_arg);
void		*philo_check(void *philo_arg);
int			philo_take_forks(t_philo *philo);
int			philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);
void		philo_clean_forks(t_philo *philo);

/* Utility functions */
uintmax_t	retrieve_time_since_ms(uintmax_t start);
uintmax_t	retrieve_time_us(void);
void		u_sleep_better(uintmax_t usec);
int			lock_check(t_philo *philo, t_mutex *lock, const char *fn);
int			update_eat_time(t_philo *philo);
int			status_change_message(t_philo *philo, const char *message, \
		t_msg_type type);
void		print_message(t_philo *philo, const char *message);
int			print_error(t_error err);

/* State checking */
void		*handle_death(t_philo *philo);
void		*handle_full_philo(t_philo *philo);
bool		gameover(t_philo *philo);
bool		has_eaten_enough(t_philo *philo);
void		set_dead(t_philo *philo);

#endif