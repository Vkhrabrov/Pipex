/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:39:25 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:17 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "../libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

static int	ft_right_cs_zeroes(t_print *tab, char *a,
				int len, int pad);
int			ft_printf_unsigned_int_helper(t_print *tab,
				char *j, unsigned int a);

int	ft_right_cs_unsigned_int(t_print *tab, char *a)
{
	int	len;
	int	pad;
	int	i;

	i = 0;
	len = ft_strlen(a);
	pad = 0;
	if (tab->wdt > len && !tab->zero)
	{
		pad = tab->wdt - len;
		if (!tab->sign && tab->sp)
			pad = tab->wdt - len;
		if (tab->pnt != 0 && tab->prc > len)
			pad = tab->wdt - tab->prc;
		if (tab->prc < len)
			pad = tab->wdt - len;
		while (pad--)
		{
			if (print(tab, ' ') == -1)
				return (-1);
		}
	}
	if (ft_right_cs_zeroes(tab, a, len, pad) == -1)
		return (-1);
	return (0);
}

static int	ft_right_cs_zeroes(t_print *tab, char *a,
				int len, int pad)
{
	int	i;

	i = 0;
	if (tab->wdt > len && tab->zero && tab->pnt)
	{
		tab->zero = 0;
		if (ft_right_cs_unsigned_int(tab, a) == -1)
			return (-1);
		return (0);
	}
	if (tab->wdt > len && tab->zero && !tab->pnt)
	{
		pad = tab->wdt - len;
		while (pad--)
		{
			if (print(tab, '0') == -1)
				return (-1);
		}
	}
	return (0);
}

static int	ft_left_cs(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	pad = 0;
	if (tab->wdt > len)
	{
		pad = tab->wdt - len;
		if (tab->pnt != 0 && tab->prc > len)
			pad = tab->wdt - tab->prc;
		if (tab->prc < len)
			pad = tab->wdt - len;
		while (pad--)
		{
			if (print(tab, ' ') == -1)
				return (-1);
		}
	}
	return (0);
}

int	ft_precision_unsigned_int(t_print *tab, char *j, size_t i)
{
	size_t	k;

	if (tab->pnt && (size_t)tab->prc > ft_strlen(j))
	{
		k = tab->prc - ft_strlen(j);
		while (k--)
		{
			if (print(tab, '0') == -1)
				return (-1);
		}
	}
	while (j[i])
	{
		if (print(tab, j[i]) == -1)
			return (-1);
		i++;
	}
	if (tab->wdt && tab->dash && tab->wdt >= tab->prc)
	{
		if (ft_left_cs(tab, j) == -1)
			return (-1);
	}
	return (0);
}

int	ft_printf_unsigned_int(t_print *tab)
{
	char			*j;
	unsigned int	a;

	a = va_arg(tab->args, unsigned int);
	j = ft_utoa(a);
	if (!j)
		return (-1);
	if (ft_printf_unsigned_int_helper(tab, j, a) == -1)
	{
		return (-1);
	}
	return (0);
}
