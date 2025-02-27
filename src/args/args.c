/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:03:32 by antoinemura       #+#    #+#             */
/*   Updated: 2025/02/27 14:57:06 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char *arg, ssize_t *result)
{
	long	val;

	val = ft_atoi(arg);
	if (val <= 0 || val > INT_MAX)
		return (false);
	*result = val;
	return (true);
}

bool	handle_args(int argc, char **argv, t_data *data)
{
	if (!is_int(argv[1], &data->nb_philo) 
		|| !is_int(argv[2], &data->time_to_die)
		|| !is_int(argv[3], &data->time_to_eat)
		|| !is_int(argv[4], &data->time_to_sleep))
		return (false);
	if (argc == 6 && !is_int(argv[5], &data->must_eat))
		return (false);
	return (true);
}
