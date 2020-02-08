/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:43 by clanglai          #+#    #+#             */
/*   Updated: 2020/02/08 12:00:13 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_zone		*find_zone_in_list(void *ptr)
{
	t_zone	*tmp_zone;

	if (ptr)
	{
		if (g_info == NULL || ptr == NULL)
			return (NULL);
		tmp_zone = g_info->start;
		while (tmp_zone)
		{
			if ((void*)tmp_zone < ptr
			&& (void*)(tmp_zone + tmp_zone->size / sizeof(t_zone)) > ptr)
			{
				break ;
			}
			tmp_zone = tmp_zone->next;
		}
		return (tmp_zone);
	}
	return (NULL);
}

static void	handle_large_zone(t_zone *used_zone)
{
	if (used_zone->prev)
		used_zone->prev->next = used_zone->next;
	if (used_zone->next)
		used_zone->next->prev = used_zone->prev;
	if (used_zone == g_info->start)
	{
		if (g_info->start->prev)
			g_info->start = used_zone->prev;
		else
			g_info->start = used_zone->next;
	}
}

void		free(void *ptr)
{
	t_alloc	*tmp;
	t_zone	*used_zone;

	used_zone = find_zone_in_list(ptr);
	if (used_zone && used_zone->status == LARGE_STATUS)
		handle_large_zone(used_zone);
	else if (used_zone)
	{
		tmp = used_zone->start;
		while (tmp)
		{
			if ((void*)tmp + sizeof(t_alloc) == ptr)
			{
				tmp->status = NOALLOC;
				break;
			}
			tmp = tmp->next;
		}
	}
}
