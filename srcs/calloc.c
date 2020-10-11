/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: langlaitcorentin <langlaitcorentin@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 08:40:04 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/10 23:06:48 by langlaitcor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	*calloc(size_t count, size_t size) {
	size_t	idx;
	void	*alloc;
	
	idx = 0;
	if (count == 0 || size == 0) {
		return NULL;
	}
	alloc = malloc(count * size);
	if (alloc == NULL)
		return NULL;
	ft_bzero(alloc, size * count);
	return (alloc);
}
