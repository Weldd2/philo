/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:03:32 by antoinemura       #+#    #+#             */
/*   Updated: 2025/02/27 12:08:49 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
