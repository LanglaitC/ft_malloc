/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:43 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/15 16:57:54 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

// void	find_in_list(void *ptr)
// {
// 	t_zone	*tmp;
// 	t_alloc	*tmp_zone;

// 	tmp = global_info->start;
// 	while (tmp && (void*)tmp > ptr && tmp->end < ptr)
// 	{
// 		tmp = tmp->next;
// 	}
// 	if (tmp && tmp->status == LARGE_STATUS)
// 	{
// 		if (tmp->prev)
// 			tmp->prev->next = tmp->next;
// 		if (tmp->next)
// 			tmp->next->prev = tmp->prev;
// 		if (tmp == global_info->start)
// 			global_info->start = global_info->start->next;
// 		munmap(tmp, tmp->start->size + sizeof(t_zone));
// 	} else if (tmp) {
// 		tmp_zone = tmp->start;
// 		while (tmp_zone)
// 		{
// 			if (tmp_zone->address == ptr)
// 				tmp->free_nbr++;
// 				tmp_zone->status = NOALLOC;
// 			tmp_zone = tmp_zone->next;
// 		}
// 	}
// }

void	free(void *ptr)
{
	(void)ptr;
	// ft_putstr("free\n");
	// if (ptr && global_info != NULL)
	// {
	// 	find_in_list(ptr);
	// }
}
