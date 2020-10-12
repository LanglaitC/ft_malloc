/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 08:03:04 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/12 08:17:17 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*alloc;

	if (count == 0 || size == 0)
		return (NULL);
	alloc = malloc(count * size);
	if (alloc == NULL)
		return (NULL);
	ft_bzero(alloc, size * count);
	return (alloc);
}
