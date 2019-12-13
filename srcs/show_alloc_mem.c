/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:05:59 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/13 16:42:45 by clanglai         ###   ########.fr       */
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

void    show_zone(t_zone* zone_start, t_alloc *start) {
    t_alloc *tmp;
    int i;

    i = 0;
    tmp = start;
    ft_putstr("0x");
    ft_putadrr((int)zone_start, "0123456789ABCDEF");
    ft_putstr(" --- size: ");
    ft_putnbr(zone_start->size);
    ft_putchar('\n');
    while (tmp) {
        if (tmp->status == ALLOCATED) {
            ft_putstr("0x");
            ft_putadrr((int)tmp->address, "0123456789ABCDEF");
            ft_putstr(" - 0x");
            ft_putadrr((int)(tmp->address + tmp->size), "0123456789ABCDEF");
            ft_putstr(" : ");
            ft_putnbr(tmp->size);
            ft_putstr(" octets\n");
        }
        tmp = tmp->next;
        i++;
    }
}

void    show_alloc_mem() {
    t_zone  *tmp;
    char    *types[3];

    ft_putstr("\n------------------ SHOW ------------------\n");
    types[0] = "TINY : ";
    types[1] = "SMALL : ";
    types[2] = "MEDIUM : ";
    if (global_info != NULL) {
        tmp = global_info->start;
        while (tmp) {
            ft_putstr(types[tmp->status]);
            show_zone(tmp, tmp->start);
            tmp = tmp->next;
            ft_putstr("\n");
        }
    }
}