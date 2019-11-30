/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:43 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/30 15:54:47 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	find_in_list(void *ptr)
{
	t_zone	*tmp;
	t_alloc	*tmp_zone;

	tmp = global_info->start;
	while (tmp && (void*)tmp > ptr && tmp->end < ptr)
	{
		tmp = tmp->next;
	}
	if (tmp && tmp->status == LARGE_STATUS)
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp == global_info->start)
			global_info->start = global_info->start->next;
		munmap(tmp, tmp->start->size + sizeof(t_zone));
	} else if (tmp) {
		tmp_zone = tmp->start;
		while (tmp_zone)
		{
			if (tmp_zone->address == ptr)
				tmp->free_nbr++;
				tmp_zone->status = NOALLOC;
			tmp_zone = tmp_zone->next;
		}
	}
}

t_zone	*find_zone_in_list(void *ptr) {
	t_zone *tmp_zone;

	if (global_info == NULL || ptr == NULL)
		return NULL;
	tmp_zone = global_info->start;
	while (tmp_zone && (int)tmp_zone > (int)ptr && (int)tmp_zone->end < (int)ptr) {
		tmp_zone = tmp_zone->next;
	}
	return tmp_zone;
}

void	free(void *ptr)
{
	(void)ptr;
	t_alloc	*tmp;
	t_zone	*used_zone;
	
	used_zone = find_zone_in_list(ptr);
	if (used_zone && used_zone->status == LARGE_STATUS)
	{
		if (used_zone->prev)
			used_zone->prev->next = used_zone->next;
		if (used_zone->next)
			used_zone->next->prev = used_zone->prev;
		if (used_zone == global_info->start)
		{
			if (global_info->start->prev) {
				global_info->start = used_zone->start->prev;
			} else {
				global_info->start = used_zone->start->next;
			}
		}
		munmap(used_zone, used_zone->start->size + (sizeof(t_zone) / sizeof(int)));
	} else if (used_zone) {
		tmp = used_zone->start;
		while (tmp)
		{
			if (tmp->address == ptr)
				used_zone->free_nbr++;
				tmp->status = NOALLOC;
			tmp = tmp->next;
		}
	}
}
