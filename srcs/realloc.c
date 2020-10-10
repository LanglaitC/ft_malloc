/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: langlaitcorentin <langlaitcorentin@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:47 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/10 15:43:17 by langlaitcor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

int				get_status(size_t size)
{
	if (size < TINY)
		return (TINY_STATUS);
	else if (size < SMALL)
		return (SMALL_STATUS);
	return (LARGE_STATUS);
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
	//ft_putstr("END REALLOC\n");
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

	(void)ptr;
	//ft_putstr("START_REALLOC\n");
	if (ptr == NULL) {
		//ft_putstr("END REALLOC\n");
		return (malloc(size));
	}
	else if (size == 0)
	{
		//ft_putstr("END_REALLOC\n");
		free(ptr);
		return (NULL);
	}
	allocated_zone = find_zone_in_list(ptr);
	allocated_ptr = find_alloc_in_list(ptr, allocated_zone);
	if (allocated_ptr)
	{
		status = get_status(allocated_ptr->size);
		if (status != LARGE_STATUS && status == get_status(size)
		&& allocated_ptr->next && allocated_ptr->size >= size)
		{
			//ft_putstr("END_REALLOC\n");
			allocated_ptr->size = size;
			return (ptr);
		}
		return (try_reallocate(allocated_ptr, size));
	}
	//ft_putstr("END_REALLOC\n");
	return (malloc(size));
}
