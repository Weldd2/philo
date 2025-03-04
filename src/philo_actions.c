#include "philo.h"

void	thread_print(t_data *data, int index, char *msg)
{
	long long	time;
	time = timestamp();
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", time, index, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

void	philo_eat(t_data *data, int index)
{
	pthread_mutex_lock(&data->forks[(index + (index % 2)) % data->nb_philo]);
	thread_print(data, index, "has taken a fork");
	pthread_mutex_lock(&data->forks[(index + ((index + 1) % 2)) % data->nb_philo]);
	thread_print(data, index, "has taken a fork");
	thread_print(data, index, "is eating");
	set_philo_meal_time(data, index, timestamp());
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[(index + (index % 2)) % data->nb_philo]);
	pthread_mutex_unlock(&data->forks[(index + ((index + 1) % 2)) % data->nb_philo]);
}

void	philo_sleep(t_data *data, int index)
{
	thread_print(data, index, "is sleeping");
	ft_usleep(data->time_to_sleep);
}
