/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:47 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/14 17:14:48 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

int				get_status(size_t size)
{
	if (size < TINY) {
		return TINY_STATUS;
	} else if (size < SMALL) {
		return SMALL_STATUS;
	}
	return LARGE_STATUS;
}

static void		*try_reallocate(t_alloc *initial, size_t size)
{
	void	*new;
	size_t	max_size;

	max_size = initial->size > size ? size : initial->size;
	new = malloc(size);
	if (new)
	{
		memcpy(new, initial->address, max_size);
		free(initial->address);
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
			status = get_status(allocated_ptr->size);
			if (status != LARGE_STATUS && status == get_status(size))
			{
				allocated_ptr->size = size;
				ft_putstr("-------- End Realloc ---------\n");
				return (ptr);
			}
			ft_putstr("-------- End Realloc ---------\n");
			return try_reallocate(allocated_ptr, size);
		}
		ft_putstr("-------- End Realloc ---------\n");
		return (malloc(size));
	}
	ft_putstr("-------- End Realloc ---------\n");
	return (NULL);
}
