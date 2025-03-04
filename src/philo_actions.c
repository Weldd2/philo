#include "philo.h"

void	thread_print(t_data *data, int index, char *msg)
{
	if (is_dead(data))
		return ;
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms(), index, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

void	philo_eat(t_data *data, int index)
{
	pthread_mutex_lock(&data->forks[(index + (index % 2)) % data->nb_philo]);
	thread_print(data, index, "has taken a fork");
	if (data->nb_philo != 1)
	{
		pthread_mutex_lock(&data->forks[(index + ((index + 1) % 2)) % data->nb_philo]);
		thread_print(data, index, "has taken a fork");
	}
	thread_print(data, index, "is eating");
	pthread_mutex_lock(&data->philo_last_meal_mutex[index]);
	data->philo_last_meal[index] = get_time_in_ms();
	pthread_mutex_unlock(&data->philo_last_meal_mutex[index]);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[(index + (index % 2)) % data->nb_philo]);
	pthread_mutex_unlock(&data->forks[(index + ((index + 1) % 2)) % data->nb_philo]);
}

void	philo_sleep(t_data *data, int index)
{
	if (!data)
		return ;
	thread_print(data, index, "is sleeping");
	usleep(data->time_to_sleep * 1000);
}
