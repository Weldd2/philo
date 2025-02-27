/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:36:58 by antoinemura       #+#    #+#             */
/*   Updated: 2025/02/27 12:08:17 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(t_mgc *mgc, char *error_msg)
{
	fprintf(stderr, "%s", error_msg);
	if (errno)
		fprintf(stderr, ": %s\n", strerror(errno));
	else
		printf("\n");
	mgc_free(mgc);
	exit(EXIT_FAILURE);
}
