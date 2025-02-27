#include "philo.h"

void	thread_print(t_data *data, int index, char *msg)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms(), index, msg);
	fflush(stdout);
	pthread_mutex_unlock(&data->print_mutex);
}

void	philo_eat(t_data *data, int index)
{
	if (index % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[index]);
		thread_print(data, index, "has taken a fork");
		pthread_mutex_lock(&data->forks[(index + 1) % data->nb_philo]);
		thread_print(data, index, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[(index + 1) % data->nb_philo]);
		thread_print(data, index, "has taken a fork");
		pthread_mutex_lock(&data->forks[index]);
		thread_print(data, index, "has taken a fork");
	}
	thread_print(data, index, "is eating");
	pthread_mutex_lock(&data->philo_last_meal_mutex[index]);
	data->philo_last_meal[index] = get_time_in_ms();
	pthread_mutex_unlock(&data->philo_last_meal_mutex[index]);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->nb_philo]);
}

void	philo_sleep(t_data *data, int index)
{
	thread_print(data, index, "is sleeping");
	usleep(data->time_to_sleep * 1000);
}
