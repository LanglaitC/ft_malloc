/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:43 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/14 17:03:23 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_zone	*find_zone_in_list(void *ptr)
{
	t_zone	*tmp_zone;

	if (ptr)
	{
		if (g_info == NULL || ptr == NULL)
			return (NULL);
		tmp_zone = g_info->start;
		while (tmp_zone)
		{
			if ((void*)tmp_zone < ptr && (void*)(tmp_zone + tmp_zone->size / sizeof(t_zone)) > ptr)
			{
				break ;
			}
			tmp_zone = tmp_zone->next;
		}
		return (tmp_zone);
	}
	return (NULL);
}

void	free(void *ptr)
{
	(void)ptr;
	t_alloc	*tmp;
	t_zone	*used_zone;

	ft_putstr("-------- Start Free ------\n");
	used_zone = find_zone_in_list(ptr);
	if (used_zone && used_zone->status == LARGE_STATUS)
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
		munmap((void*)used_zone, used_zone->size);
	}
	else if (used_zone)
	{
		tmp = used_zone->start;
		while (tmp)
		{
			if (tmp->address == ptr)
			{
				used_zone->free_nbr++;
				tmp->status = NOALLOC;
			}
			tmp = tmp->next;
		}
	}
	ft_putstr("-------- End Free ------\n");
}
