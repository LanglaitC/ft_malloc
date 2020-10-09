/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: langlaitcorentin <langlaitcorentin@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 08:40:04 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/09 14:36:14 by langlaitcor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	*calloc(size_t count, size_t size) {
	size_t	idx;
	void	*alloc;
	
	// ft_putstr("START CALLOC --\n");
	idx = 0;
	if (count == 0 || size == 0) {
		return NULL;
	}
	alloc = malloc(count * size);
	if (alloc == NULL) {
		// ft_putstr("END CALLOC --\n");
		return NULL;
	}
	ft_memset(alloc, 0, size * count);
	// ft_putstr("END CALLOC --\n");
	return (alloc);
}
