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
	pthread_t		*philo;
	ssize_t			nb_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_sleep;
	ssize_t			time_to_eat;
	ssize_t			must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	bool			stop_flag;
}	t_data;

typedef int	(*t_validator)(char *arg, void *result);

typedef struct s_philo_args
{
	t_data	*data;
	int		index;
}	t_philo_args;

int			is_int(char *arg, void *result);
void		*philo_lifecycle(void *arg);
bool		handle_args(int argc, char **argv, t_data *data);
bool		check_args(int argc, char **argv, int expected_args,
				t_validator validators[], void *results[]);
long long	ft_atoi(const char *nptr);
void		philo_eat(t_data *data, int index);
void		philo_think(t_data *data, int index);
void		philo_sleep(t_data *data, int index);
long long	get_time_in_ms(void);
void		ft_error(t_mgc *mgc, char *error_msg);

#endif
