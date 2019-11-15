/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:05:59 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/15 16:34:06 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    show_zone(t_alloc *start) {
    t_alloc *tmp;
    int i;

    i = 0;
    tmp = start;
    while (tmp) {
        if (tmp->status == ALLOCATED) {
            ft_putstr("Zone: ");
            ft_putnbr(tmp->size);
            ft_putstr("\n");
        }
        tmp = tmp->next;
        i++;
    }
}

void    show_alloc_mem() {
    t_zone  *tmp;
    char    *types[3];

    types[0] = "TINY :\n";
    types[1] = "SMALL :\n";
    types[2] = "MEDIUM :\n";
    if (global_info != NULL) {
        tmp = global_info->start;
        while (tmp) {
            ft_putstr(types[tmp->status]);
            show_zone(tmp->start);
            tmp = tmp->next;
            ft_putstr("\n");
        }
    }
    ft_putstr("\n------------------ SHOW ------------------\n");
}