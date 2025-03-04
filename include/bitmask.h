/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:32:24 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 14:18:59 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMASK_H
# define BITMASK_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# define BITS_PER_WORD (sizeof(word_t) * 8)

typedef unsigned long long	word_t;

typedef struct s_bitmask
{
	word_t	*words;
	int		nbits;
	int		nwords;
	int		count;
}	t_bitmask;

t_bitmask	*bitmask_create(int nbits);
void	bitmask_set(t_bitmask *bitmask, int index);
bool	are_bitmask_all_set(t_bitmask *bitmask);
void	bitmask_free(t_bitmask *mask);

#endif