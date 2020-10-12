/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 08:22:09 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/12 08:22:10 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	*create_new_chunk(t_alloc *last, int size)
{
	t_alloc	*new;
	int		to_jump;

	if (last->size % 16)
		to_jump = last->size + 16 - last->size % 16 + sizeof(t_alloc);
	else
		to_jump = last->size + sizeof(t_alloc);
	new = last + (to_jump / sizeof(t_alloc));
	last->next = new;
	new->size = size;
	new->next = NULL;
	new->status = ALLOCATED;
	if (size % 16)
		g_info->current->free_size -= (size + 16 - size % 16 + sizeof(t_alloc));
	else
		g_info->current->free_size -= (size + sizeof(t_alloc));
	return (new + (sizeof(t_alloc) / sizeof(t_alloc)));
}

void	*allocate_memory(size_t size)
{
	t_alloc	*tmp;
	t_alloc	*last;

	tmp = g_info->current->start;
	last = tmp;
	while (tmp != NULL && (tmp->status == ALLOCATED || tmp->size < size))
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		tmp->status = ALLOCATED;
		tmp->size = size;
		return (tmp + (sizeof(t_alloc) / sizeof(t_alloc)));
	}
	return (create_new_chunk(last, size));
}

void	*malloc(size_t size)
{
	void	*result;

	if (get_info_variable(size) == NULL)
		return (NULL);
	result = allocate_memory(size);
	return (result);
}
