/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:34:21 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/03 22:29:19 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmask.h"

t_bitmask	*bitmask_create(int nbits)
{
	t_bitmask	*mask;

	mask = malloc(sizeof(t_bitmask));
	if (!mask)
		return (NULL);
	mask->nbits = nbits;
	mask->nwords = (nbits + BITS_PER_WORD - 1) / BITS_PER_WORD;
	mask->words = calloc(mask->nwords, sizeof(word_t));
	if (!mask->words)
		return (free(mask), NULL);
	mask->count = 0;	
	return (mask);
}

void	bitmask_set(t_bitmask *bitmask, int index)
{
	word_t	mask;

	mask = (1ULL << index % BITS_PER_WORD);
	if ((bitmask->words[index / BITS_PER_WORD] & mask) == 0)
	{
		bitmask->words[index / BITS_PER_WORD] |= mask;
		bitmask->count++;
	}
}

bool	are_bitmask_all_set(t_bitmask *bitmask)
{
	return (bitmask->count == bitmask->nbits);
}

void	bitmask_free(t_bitmask *mask)
{
	free(mask->words);
	free(mask);
}
