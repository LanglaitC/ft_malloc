/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 08:22:23 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/12 08:42:10 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			ft_putadrr(unsigned int addr, char base[16])
{
	if (addr > 16)
		ft_putadrr(addr / 16, base);
	ft_putchar(base[addr % 16]);
}

unsigned int	show_zone(t_zone *zone_start, t_alloc *start, unsigned int acc)
{
	t_alloc	*tmp;

	tmp = start;
	ft_putstr("0x");
	ft_putadrr((uintptr_t)zone_start, "0123456789ABCDEF");
	ft_putchar('\n');
	while (tmp)
	{
		ft_putstr("0x");
		ft_putadrr((uintptr_t)tmp + sizeof(t_alloc), "0123456789ABCDEF");
		ft_putstr(" - 0x");
		ft_putadrr((uintptr_t)tmp + sizeof(t_alloc) + tmp->size,
			"0123456789ABCDEF");
		ft_putstr(" : ");
		ft_putnbr(tmp->size);
		ft_putstr(" octets\n");
		acc += tmp->size;
		tmp = tmp->next;
	}
	return (acc);
}

void			show_alloc_mem(void)
{
	t_zone			*tmp;
	char			*types[3];
	unsigned int	total;

	total = 0;
	types[0] = "TINY : ";
	types[1] = "SMALL : ";
	types[2] = "MEDIUM : ";
	if (g_info != NULL)
	{
		tmp = g_info->start;
		while (tmp)
		{
			ft_putstr(types[tmp->status]);
			total = show_zone(tmp, tmp->start, total);
			tmp = tmp->next;
		}
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}
