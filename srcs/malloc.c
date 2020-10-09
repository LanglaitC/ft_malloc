/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: langlaitcorentin <langlaitcorentin@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:45 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/09 14:43:50 by langlaitcor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	*create_new_chunk(t_alloc *last, int size)
{
	t_alloc	*new;
	int		to_jump;

	if (last == NULL)
	{
		new = g_info->current->start;
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		to_jump = last->size + sizeof(t_alloc);
		new = last + (to_jump / sizeof(t_alloc));
		last->next = new;
		new->prev = last;
	}
	new->size = size;
	new->next = NULL;
	new->address = new + (sizeof(t_alloc) / sizeof(t_alloc));
	new->status = ALLOCATED;
	g_info->current->free_size -= (size + sizeof(t_alloc));
	return (new->address);
}

void	*allocate_memory(size_t size)
{
	t_alloc	*tmp;
	t_alloc	*last;

	tmp = g_info->current->start;
	last = tmp;
	while (tmp != NULL && (tmp->status != NOALLOC || tmp->size < size))
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		tmp->status = ALLOCATED;
		tmp->size = size;
		return (tmp->address);
	}
	return (create_new_chunk(last, size));
}

void	*malloc(size_t size)
{
	void	*result;
	
	// ft_putstr("START Malloc --\n");
	if (get_info_variable(size) == NULL)
		return (NULL);
	result = allocate_memory(size);
	if (((int)result & 15) != 0) {
		ft_putstr("WTF?\n");
	}
	return (result);
}
