/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:59:50 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/05 14:55:41 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi_hexa(const char *str)
{
	size_t					i;
	size_t					j;
	unsigned long long		nb;
	int						neg;

	i = 0;
	j = 0;
	nb = 0;
	neg = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = (nb * 10) + (str[i++] - '0');
		j++;
	}
	if (neg == -1 && (nb > 9223372036854775808UL || j > 19))
		return (0);
	if (neg != -1 && (nb > 9223372036854775807UL || j > 19))
		return (-1);
	return (neg != -1 ? nb : -nb);
}
