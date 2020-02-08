/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:45 by clanglai          #+#    #+#             */
/*   Updated: 2020/02/08 11:57:54 by clanglai         ###   ########.fr       */
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
		new->next = NULL;
	}
	else
	{
		to_jump = last->size + sizeof(t_alloc);
		new = last + to_jump / sizeof(t_alloc);
		last->next = new;
	}
	new->size = size;
	new->status = ALLOCATED;
	new->next = NULL;
	// ft_putadrr((unsigned int)last, "0123456789ABCDEF");
	// ft_putstr("------ New one\n");
	// ft_putadrr((unsigned int)new, "0123456789ABCDEF");
	// ft_putstr("------ New one\n");
	return ((void*)new + sizeof(t_alloc));
}

void	*allocate_memory(size_t size)
{
	t_alloc	*tmp;
	t_alloc	*last;

	tmp = g_info->current->start;
	last = tmp;
	while (tmp != NULL && tmp->status != NOALLOC)
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		tmp->status = ALLOCATED;
		tmp->size = size;
		return ((void*)tmp + sizeof(t_alloc));
	}
	return (create_new_chunk(last, size));
}

void	*malloc(size_t size)
{
	void	*result;

	//ft_putstr("Malloc ---\n");
	if (size % 16)
		size += 16 - size % 16;
	if (get_info_variable(size) == NULL)
		return (NULL);
	//ft_putstr("Start allocate\n");
	result = allocate_memory(size);
	//ft_putstr("End Malloc\n");
	return (result);
}
