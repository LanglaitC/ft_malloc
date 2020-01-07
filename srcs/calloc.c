/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 08:40:04 by clanglai          #+#    #+#             */
/*   Updated: 2020/01/07 09:52:21 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	*calloc(size_t count, size_t size) {
	size_t	idx;
	void	*alloc;

	// ft_putstr("Calloc --\n");
	idx = 0;
	if (count == 0 || size == 0) {
		return NULL;
	}
	alloc = malloc(count * size);
	if (alloc == NULL)
		return NULL;
	ft_memset(alloc, 0, size * count);
	return (alloc);
}
