/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:38:09 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:34:57 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mgc	*mgc_init(void)
{
	t_mgc	*mgc;

	mgc = malloc(sizeof(t_mgc));
	if (!mgc)
		return (NULL);
	mgc->first = NULL;
	mgc->last = NULL;
	return (mgc);
}

void	*mgc_alloc(t_mgc *mgc, size_t size, size_t nb_elem)
{
	void	*block;

	block = malloc(size * nb_elem);
	if (!block)
		return (NULL);
	mgc_add_block(mgc, block);
	return (block);
}

void	mgc_add_block(t_mgc *mgc, void *block)
{
	t_mgc_block_list	*new_block;

	new_block = malloc(sizeof(t_mgc_block_list));
	if (!new_block)
		exit(EXIT_FAILURE);
	new_block->block = block;
	new_block->next = NULL;
	if (mgc->last)
		mgc->last->next = new_block;
	mgc->last = new_block;
	if (!mgc->first)
		mgc->first = new_block;
}

void	mgc_free(t_mgc *mgc)
{
	t_mgc_block_list	*current;
	t_mgc_block_list	*tmp;

	current = mgc->first;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->block);
		free(tmp);
		tmp = NULL;
	}
	free(mgc);
	mgc = NULL;
}
