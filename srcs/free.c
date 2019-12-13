/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:43 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/13 17:15:48 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_zone	*find_zone_in_list(void *ptr) {
	t_zone *tmp_zone;

	if (global_info == NULL || ptr == NULL)
		return NULL;
	tmp_zone = global_info->start;
	while (tmp_zone && (int)tmp_zone > (int)ptr && (void*)(tmp_zone + tmp_zone->size / sizeof(t_zone)) < ptr) {
		tmp_zone = tmp_zone->next;
	}
	return tmp_zone;
}

void	free(void *ptr)
{
	// (void)ptr;
	t_alloc	*tmp;
	t_zone	*used_zone;
	
	used_zone = find_zone_in_list(ptr);
	if (ptr) {
		if (used_zone && used_zone->status == LARGE_STATUS)
		{
			if (used_zone->prev)
				used_zone->prev->next = used_zone->next;
			if (used_zone->next)
				used_zone->next->prev = used_zone->prev;
			if (used_zone == global_info->start)
			{
				if (global_info->start->prev) {
					global_info->start = used_zone->prev;
				} else {
					global_info->start = used_zone->next;
				}
			}
			munmap((void*)used_zone, used_zone->size);
		} else if (used_zone) {
			tmp = used_zone->start;
			while (tmp)
			{
				if (tmp->address == ptr) {
					used_zone->free_nbr++;
					tmp->status = NOALLOC;
				}
				tmp = tmp->next;
			}
		}
	}
}
