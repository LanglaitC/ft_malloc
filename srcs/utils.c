/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:23:45 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/14 17:12:40 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_info				*g_info;

static t_zone_info	get_best_alloc_size_for_zone(int size, unsigned char status)
{
	int			i;
	int			size_by_status[3];
	t_zone_info info;

	size_by_status[0] = TINY;
	size_by_status[1] = SMALL;
	size_by_status[2] = size;
	info.status = status;
	if (info.status == LARGE_STATUS)
	{
		info.zone_size = (size + sizeof(t_alloc) + PAGESIZE)
		/ PAGESIZE * PAGESIZE;
		info.chunk_number = 1;
		return (info);
	}
	info.zone_size = PAGESIZE;
	i = (PAGESIZE - sizeof(t_zone)) /
	(size_by_status[info.status] + sizeof(t_alloc));
	while (i < MIN_ALLOCATION_BY_ZONE)
	{
		i += PAGESIZE / (size_by_status[info.status] + sizeof(t_alloc));
		info.zone_size += PAGESIZE;
	}
	info.chunk_number = i;
	return (info);
}

void				insert_new_zone(t_zone *new)
{
	t_zone	*tmp;

	ft_putstr("\t\t\t1-3-2-0\n");
	if (g_info->start == NULL)
		g_info->start = new;
	else
	{
		ft_putstr("\t\t\t1-3-2-1\n");
		tmp = g_info->start;
		if (tmp->prev == NULL && (int)tmp < (int)new)
		{
			ft_putstr("\t\t\t1-3-2-2\n");
			new->next = tmp;
			tmp->prev = new;
			g_info->start = new;
		}
		else
		{
			ft_putstr("\t\t\t1-3-2-3\n");
			while (tmp != NULL && (int)tmp < (int)new && tmp->next)
				tmp = tmp->next;
			ft_putstr("\t\t\t1-3-2-4\n");
			if (tmp != NULL && tmp < new)
			{
				ft_putstr("\t\t\t1-3-2-5\n");
				ft_putnbr((int)new);
				ft_putchar('\n');
				ft_putstr("\t\t\t1-3-2-6\n");
				tmp->prev->next = new;
				ft_putstr("\t\t\t1-3-2-7\n");
				new->prev = tmp->prev;
				ft_putstr("\t\t\t1-3-2-8\n");
				new->next = tmp;
				ft_putstr("\t\t\t1-3-2-9\n");
				tmp->prev = new;
				ft_putstr("\t\t\t1-3-2-10\n");
			}
			else
			{
				ft_putstr("\t\t\t1-3-2-11\n");
				tmp->next = new;
				new->prev = tmp;
			}
		}
	}
	ft_putstr("\t\t\t1-3-2-12\n");
}

static t_zone		*search_free_zone(t_zone_info info)
{
	t_zone	*tmp;

	tmp = NULL;
	if (g_info->start != NULL)
	{
		tmp = g_info->start;
		while (tmp != NULL)
		{
			if (tmp->status == info.status && tmp->free_nbr)
				break ;
			tmp = tmp->next;
		}
	}
	return (tmp);
}

static t_zone		*allocate_zone(t_zone_info info)
{
	t_zone	*tmp;

	ft_putstr("\t\t1-3-1\n");
	tmp = mmap(0, sizeof(t_zone) + info.zone_size,
	PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	ft_putstr("\t\t1-3-2\n");
	tmp->size = info.zone_size;
	tmp->status = info.status;
	tmp->free_nbr = info.chunk_number;
	tmp->start = (t_alloc*)(tmp + (sizeof(t_zone) / sizeof(t_zone)));
	tmp->start->status = NOALLOC;
	tmp->start->address = tmp->start + (sizeof(t_alloc) / sizeof(t_alloc));
	ft_putstr("\t\t1-3-3\n");
	insert_new_zone(tmp);
	ft_putstr("\t\t1-3-4\n");
	return (tmp);
}

t_info				*get_info_variable(size_t size)
{
	t_zone_info info;

	if (g_info == NULL)
	{
		g_info = mmap(0, sizeof(t_info),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	}
	ft_putstr("\t1-1\n");
	info = get_best_alloc_size_for_zone(size, get_status(size));
	ft_putstr("\t1-2\n");
	g_info->current = search_free_zone(info);
	ft_putstr("\t1-3\n");
	if (g_info->current == NULL)
	{
		g_info->current = allocate_zone(info);
	}
	ft_putstr("\t1-4\n");
	return (g_info);
}
