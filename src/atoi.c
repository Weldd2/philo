/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:45:09 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 14:50:07 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *nptr)
{
	long		ret;

	ret = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		ret *= 10;
		ret += (*nptr - '0');
		nptr++;
	}
	if (*nptr != '\0')
		return (0);
	return (ret);
}
