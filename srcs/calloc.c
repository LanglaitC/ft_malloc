/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 08:40:04 by clanglai          #+#    #+#             */
/*   Updated: 2020/01/06 15:47:19 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void *calloc(size_t count, size_t size) {
    int idx;

    idx = 0;
	if (get_info_variable(size, 1) == NULL) {
		return (NULL);
	}
    while (idx < count) {
        ft_memset(allocate_memory(size), 0, size);   
    }
    return g_info->current->start->address;
}