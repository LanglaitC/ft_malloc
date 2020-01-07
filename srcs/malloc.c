/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:45 by clanglai          #+#    #+#             */
/*   Updated: 2020/01/07 17:40:20 by clanglai         ###   ########.fr       */
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
	new->address = new + (sizeof(t_alloc) / sizeof(t_alloc));
	new->status = ALLOCATED;
	return (new->address);
}

void	*allocate_memory(size_t size)
{
	t_alloc	*tmp;
	t_alloc	*last;

	g_info->current->free_size -= (size + sizeof(t_alloc));
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

	ft_putstr("Malloc -- 1");
	if (get_info_variable(size) == NULL)
		return (NULL);
	ft_putstr("Malloc -- 2");
	result = allocate_memory(size);
	ft_putstr("Malloc -- 3\n");
	return (result);
}
