/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: langlaitcorentin <langlaitcorentin@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:43 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/10 17:54:45 by langlaitcor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_zone		*find_zone_in_list(void *ptr)
{
	t_zone	*tmp_zone;

	tmp_zone = NULL;
	if (ptr && g_info != NULL)
	{
		tmp_zone = g_info->start;
		while (tmp_zone)
		{
			if ((unsigned int)tmp_zone < (unsigned int)ptr
			&& (unsigned int)tmp_zone + tmp_zone->size > (unsigned int)ptr)
			{
				break ;
			}
			tmp_zone = tmp_zone->next;
		}
	}
	return (tmp_zone);
}

static void	handle_large_zone(t_zone *used_zone)
{
	if (used_zone->prev)
		used_zone->prev->next = used_zone->next;
	if (used_zone->next)
		used_zone->next->prev = used_zone->prev;
	if (used_zone == g_info->start)
	{
		g_info->start = used_zone->next;
	}
	munmap(used_zone, used_zone->size+sizeof(t_zone));
}

void		free(void *ptr)
{
	(void)ptr;
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
			if (tmp->address == ptr)
				tmp->status = NOALLOC;
			tmp = tmp->next;
		}
	}
}
