#ifndef PHILO_H
# define PHILO_H

#include "mgc.h"
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

# ifdef DEBUG
#  include <assert.h>
#  define EX(fmt, ...) \
	do { \
		fprintf(stderr, "%s:%d, %s: " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
		abort(); \
	} while (0)
#endif

typedef struct s_data
{
	bool			stop_flag;
	pthread_t		*philo;
	pthread_t		reaper;
	ssize_t			*philo_meal_count;
	long long 		*philo_last_meal;
	ssize_t			nb_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_sleep;
	ssize_t			time_to_eat;
	ssize_t			must_eat;
	pthread_mutex_t	*philo_meal_count_mutex;
	pthread_mutex_t	*philo_last_meal_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
}	t_data;

typedef int	(*t_validator)(char *arg, void *result);

typedef struct s_philo_args
{
	t_data	*data;
	int		index;
}	t_philo_args;

long long	get_time_in_ms(void);
void		die(t_data *data, int index);
int			is_int(char *arg, ssize_t *result);
void		*philo_lifecycle(void *arg);
bool		handle_args(int argc, char **argv, t_data *data);
bool		check_args(int argc, char **argv, int expected_args,
				t_validator validators[], void *results[]);
long		ft_atoi(const char *nptr);
void		philo_eat(t_data *data, int index);
void		thread_print(t_data *data, int index, char *msg);
void		philo_sleep(t_data *data, int index);
void		ft_error(t_mgc *mgc, char *error_msg);
void		*reaper(void *void_data);
bool		is_dead(t_data *data);
ssize_t		get_philo_meal_count(t_data *data, int index);
void		increment_philo_meal_count(t_data *data, int index);
long long	get_philo_meal_time(t_data *data, int index);
void		set_philo_meal_time(t_data *data, int index, long long value);


#endif
