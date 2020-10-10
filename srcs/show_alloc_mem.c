/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: langlaitcorentin <langlaitcorentin@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:05:59 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/10 15:59:06 by langlaitcor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_putadrr(unsigned int addr, char base[16])
{
	if (addr > 16)
		ft_putadrr(addr / 16, base);
	ft_putchar(base[addr % 16]);
}

void	show_zone(t_zone *zone_start, t_alloc *start)
{
	t_alloc	*tmp;
	int		i;

	i = 0;
	tmp = start;
	ft_putstr("0x");
	ft_putadrr((unsigned int)zone_start, "0123456789ABCDEF");
	ft_putstr(" - ");
	ft_putadrr((unsigned int)zone_start + zone_start->size, "0123456789ABCDEF");
	ft_putchar('\n');
	while (tmp)
	{
		ft_putstr("0x");
		ft_putadrr((unsigned int)tmp->address, "0123456789ABCDEF");
		ft_putstr(" - 0x");
		ft_putadrr((unsigned int)(tmp->address + tmp->size),
			"0123456789ABCDEF");
		ft_putstr(" : ");
		ft_putnbr(tmp->size);
		ft_putstr(" octets\n");
		tmp = tmp->next;
		i++;
	}
}

void	show_alloc_mem(void)
{
	t_zone	*tmp;
	char	*types[3];

	types[0] = "TINY : ";
	types[1] = "SMALL : ";
	types[2] = "MEDIUM : ";
	if (g_info != NULL)
	{
		tmp = g_info->start;
		while (tmp)
		{
			ft_putstr(types[tmp->status]);
			show_zone(tmp, tmp->start);
			tmp = tmp->next;
			ft_putstr("\n");
		}
	}
}
