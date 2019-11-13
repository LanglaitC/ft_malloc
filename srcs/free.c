/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:43 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/13 15:44:02 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	free_ptr(t_alloc *found_ptr, t_alloc* last, size_t position)
{
	if (position < 2)
	{
		found_ptr->status = NOALLOC;
	} else 
	{
		if (found_ptr == last)
		{
			munmap(found_ptr, found_ptr->size);
			global_info->large = NULL;
		} else
		{
			last->next = found_ptr->next;
			munmap(found_ptr, found_ptr->size);
		}
	}
}

void	find_in_list(void *ptr, t_alloc *ptr_arr[3])
{
	int		i;
	t_alloc	*tmp;
	t_alloc *last;

	i = 0;
	while (i < 3)
	{
		tmp = ptr_arr[i];
		last = tmp;
		while (tmp)
		{
			if (tmp->address == ptr)
			{
				free_ptr(tmp, last, i);
				return;
			}
			last = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

void	free(void *ptr)
{
	t_alloc	*ptr_arr[3];

	ptr_arr[0] = global_info->small;
	ptr_arr[1] = global_info->medium;
	ptr_arr[2] = global_info->large;
	if (ptr && global_info != NULL)
	{
		find_in_list(ptr, ptr_arr);
	}
}
