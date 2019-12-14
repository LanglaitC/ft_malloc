/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:47 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/14 14:33:54 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

static void		*try_reallocate(t_zone *zone, void *init_ptr, size_t size)
{
	void *new;

	(void)zone;
	new = malloc(size);
	if (new)
	{
		ft_memcpy(new, init_ptr, size);
	}
	return (new);
}

static t_alloc	*find_alloc_in_list(void *ptr, t_zone *zone)
{
	t_alloc *tmp;

	if (zone != NULL)
	{
		tmp = zone->start;
		while (tmp)
		{
			if (tmp->address == ptr)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	*allocated_zone;
	t_alloc	*allocated_ptr;
	char	status;

	ft_putstr("-------- Start Realloc -------\n");
	if (ptr == NULL)
	{
		ft_putstr("-------- End Realloc ---------\n");
		return (malloc(size));
	}
	else if (size == 0)
		free(ptr);
	else
	{
		allocated_zone = find_zone_in_list(ptr);
		allocated_ptr = find_alloc_in_list(ptr, allocated_zone);
		if (allocated_ptr)
		{
			status = GET_STATUS(allocated_ptr->size);
			if (status < LARGE_STATUS && status == GET_STATUS(size))
			{
				allocated_ptr->size = size;
				return (ptr);
			}
			else if (status == LARGE_STATUS && status == GET_STATUS(size))
			{
				ft_putstr("-------- End Realloc ---------\n");
				return (try_reallocate(allocated_zone, ptr, size));
			}
			else
			{
				free(ptr);
				ft_putstr("-------- End Realloc ---------\n");
				return (malloc(size));
			}
		}
		ft_putstr("-------- End Realloc ---------\n");
		return (malloc(size));
	}
	ft_putstr("-------- End Realloc ---------\n");
	return (NULL);
}
