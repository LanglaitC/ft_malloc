/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:47 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/15 12:21:01 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void    *realloc(void* ptr, size_t size) {
    // write(1, "realloc\n", 8);
    (void)ptr;
    // if (ptr == NULL) {
        return malloc(size);
    // }
    // return NULL;
}