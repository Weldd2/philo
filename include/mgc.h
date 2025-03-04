/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:04:32 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/04 19:34:57 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MGC_H
# define MGC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_mgc_block_list
{
	void					*block;
	struct s_mgc_block_list	*next;
}	t_mgc_block_list;

typedef struct s_mgc
{
	struct s_mgc_block_list	*first;
	struct s_mgc_block_list	*last;
}	t_mgc;

t_mgc		*mgc_init(void);
void		*mgc_alloc(t_mgc *mgc, size_t size, size_t nb_elem);
void		mgc_add_block(t_mgc *mgc, void *block);
void		mgc_free(t_mgc *mgc);

#endif