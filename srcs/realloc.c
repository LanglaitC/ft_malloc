/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:47 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/13 15:35:45 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *realloc(void* ptr, size_t size) {
    // write(1, "realloc\n", 8);
    (void)ptr;
    // if (ptr == NULL) {
        return malloc(size);
    // }
    // return NULL;
}