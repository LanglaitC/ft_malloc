/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 08:21:26 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/15 12:05:10 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_info				*g_info;

static t_zone_info	get_best_alloc_size_for_zone(int size)
{
	int			i;
	int			size_by_status[3];
	t_zone_info info;

	size_by_status[0] = TINY;
	size_by_status[1] = SMALL;
	size_by_status[2] = size;
	info.status = get_status(size);
	if (info.status == LARGE_STATUS)
	{
		info.zone_size = (size + sizeof(t_zone) + sizeof(t_alloc)
		+ getpagesize()) / getpagesize() * getpagesize();
		info.chunk_number = 1;
		return (info);
	}
	info.zone_size = getpagesize();
	i = (getpagesize() - sizeof(t_zone)) /
	(size_by_status[info.status] + sizeof(t_alloc));
	while (i < MIN_ALLOCATION_BY_ZONE)
	{
		i += getpagesize() / (size_by_status[info.status] + sizeof(t_alloc));
		info.zone_size += getpagesize();
	}
	info.chunk_number = i;
	return (info);
}

void				insert_new_zone(t_zone *new)
{
	t_zone	*tmp;

	tmp = g_info->start;
	if ((uintptr_t)tmp > (uintptr_t)new)
	{
		new->next = tmp;
		tmp->prev = new;
		g_info->start = new;
		return ;
	}
	while ((uintptr_t)tmp < (uintptr_t)new && tmp->next)
		tmp = tmp->next;
	if (tmp->next)
	{
		if (tmp->prev)
			tmp->prev->next = new;
		new->prev = tmp->prev;
		new->next = tmp;
		tmp->prev = new;
		return ;
	}
	tmp->next = new;
	new->prev = tmp;
}

static t_zone		*search_free_zone(t_zone_info info, size_t size)
{
	t_zone	*tmp;
	t_alloc *tmp_alloc;

	if (g_info->start == NULL)
		return (NULL);
	tmp = g_info->start;
	while (tmp != NULL)
	{
		if (tmp->status == info.status && tmp->status != LARGE_STATUS)
		{
			if (tmp->free_size >= size + sizeof(t_alloc))
				break ;
			tmp_alloc = tmp->start;
			while (tmp_alloc != NULL)
			{
				if (tmp_alloc->status == NOALLOC && tmp_alloc->size >= size)
					return (tmp);
				tmp_alloc = tmp_alloc->next;
			}
		}
		tmp = tmp->next;
	}
	return (tmp);
}

static t_zone		*allocate_zone(t_zone_info info, size_t size)
{
	t_zone	*tmp;

	tmp = mmap(0, sizeof(t_zone) + info.zone_size,
	PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == NULL)
		return (NULL);
	tmp->size = info.zone_size;
	tmp->status = info.status;
	tmp->free_size = tmp->size - sizeof(t_zone) - size - sizeof(t_alloc);
	tmp->start = (t_alloc*)(tmp + (sizeof(t_zone) / sizeof(t_zone)));
	tmp->start->status = NOALLOC;
	tmp->start->size = size;
	if (g_info->start == NULL)
		g_info->start = tmp;
	else
		insert_new_zone(tmp);
	return (tmp);
}

t_info				*get_info_variable(size_t size)
{
	t_zone_info info;

	if (g_info == NULL)
	{
		g_info = mmap(0, sizeof(t_info),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_info == NULL)
			return (NULL);
	}
	info = get_best_alloc_size_for_zone(size);
	g_info->current = search_free_zone(info, size);
	if (g_info->current == NULL)
	{
		g_info->current = allocate_zone(info, size);
		if (g_info->current == NULL)
			return (NULL);
	}
	return (g_info);
}
