/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:05:59 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/30 14:43:34 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// ft_puta

void    ft_putadrr(int addr, char base[16]) {
    if ((int)addr > 16) {
        ft_putadrr(addr / 16, base);
    }
    ft_putchar(base[addr % 16]);
}

void    show_zone(t_alloc *start) {
    t_alloc *tmp;
    int i;

    i = 0;
    tmp = start;
    while (tmp) {
        if (tmp->status == ALLOCATED) {
            ft_putstr("Zone: ");
            ft_putadrr((int)tmp, "0123456789abcdef");
            ft_putstr(" - ");
            ft_putadrr((int)tmp->address, "0123456789abcdef");
            ft_putstr("\n");
        }
        tmp = tmp->next;
        i++;
    }
}

void    show_alloc_mem() {
    t_zone  *tmp;
    char    *types[3];

    ft_putstr("\n------------------ SHOW ------------------\n");
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
}