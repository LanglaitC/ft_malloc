/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:23:45 by clanglai          #+#    #+#             */
/*   Updated: 2020/02/08 11:54:12 by clanglai         ###   ########.fr       */
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
		info.zone_size = (size + sizeof(t_alloc) + PAGESIZE)
		/ PAGESIZE * PAGESIZE;
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
	return (info);
}

void				insert_new_zone(t_zone *new)
{
	t_zone	*tmp;

	tmp = g_info->start;
	if (tmp->prev == NULL && (unsigned int)tmp < (unsigned int)new)
	{
		new->next = tmp;
		tmp->prev = new;
		g_info->start = new;
	}
	else
	{
		while (tmp != NULL && (unsigned int)tmp < (unsigned int)new && tmp->next)
			tmp = tmp->next;
		if (tmp != NULL && tmp->next)
		{
			if (tmp->prev) {
				tmp->prev->next = new;
			}
			new->prev = tmp->prev;
			new->next = tmp;
			tmp->prev = new;
		}
		else
		{
			tmp->next = new;
			new->prev = tmp;
		}
	}
}

int	got_free_chunk(t_zone *zone, size_t size)
{
	t_alloc			*tmp;
	unsigned int	new_adress;

	//ft_putstr("\t\t\t1\n");
	tmp = zone->start;
	while (tmp->next)
	{
		//ft_putstr("\t\t\t2\n");
		if (tmp->status == NOALLOC && tmp->size >= size)
			return (1);
		ft_putadrr((unsigned int)tmp->next, "0123456789ABCDEF");
		ft_putstr("------ Breuh\n");
		tmp = tmp->next;
	}
	new_adress = (unsigned int)tmp + tmp->size + sizeof(t_alloc);
	//ft_putstr("\t\t\t3\n");
	if (new_adress + size + sizeof(t_alloc) < (unsigned int)zone + zone->size)
		return (1);
	return (0);
}

static t_zone		*search_free_zone(t_zone_info info, size_t size)
{
	t_zone	*tmp;

	tmp = NULL;
	if (g_info->start != NULL && info.status != LARGE_STATUS)
	{
		tmp = g_info->start;
		//ft_putstr("\t\t1\n");
		while (tmp != NULL)
		{
			//ft_putstr("\t\t2\n");
			if (tmp->status == info.status && got_free_chunk(tmp, size))
				break ;
			tmp = tmp->next;
		}
		//ft_putstr("\t\t3\n");
	}
	return (tmp);
}

static t_zone		*allocate_zone(t_zone_info info)
{
	t_zone	*tmp;

	tmp = mmap(0, sizeof(t_zone) + info.zone_size,
	PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == NULL) {
		return (NULL);
	}
	tmp->size = info.zone_size;
	tmp->status = info.status;
	tmp->start = (t_alloc*)(tmp + (sizeof(t_zone) / sizeof(t_zone)));
	tmp->start->status = NOALLOC;
	if (g_info->start == NULL)
		g_info->start = tmp;
	else 
		insert_new_zone(tmp);
	return (tmp);
}

t_info				*get_info_variable(size_t size)
{
	t_zone_info info;

	//ft_putstr("\t1\n");
	if (g_info == NULL)
	{
		g_info = mmap(0, sizeof(t_info),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_info == NULL) {
			return (NULL);
		}
	}
	info = get_best_alloc_size_for_zone(size);
	//ft_putstr("\t2\n");
	g_info->current = search_free_zone(info, size);
	//ft_putstr("\t3\n");
	if (g_info->current == NULL)
	{
		g_info->current = allocate_zone(info);
		//ft_putstr("\t4\n");
		if (g_info->current == NULL) {
			return (NULL);
		}
	}
	//ft_putstr("\t5\n");
	return (g_info);
}
