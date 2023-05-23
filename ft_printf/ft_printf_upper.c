/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 22:56:48 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:13 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "../libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_right_cs_zeroes(t_print *tab, char *a, int len);
int			calculate_padding_x_left(t_print *tab, char *a, int len, int pad);
int			upper_x_zeroes_support(t_print *tab, int pad, int len, char *a);
int			lower_precision_support(t_print *tab, char *j);

int	ft_right_cs_x_upper(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	pad = calculate_padding_x(tab, a, len);
	if (tab->wdt > len && !tab->zero)
	{
		while (pad--)
		{
			if (print(tab, ' ') == -1)
				return (-1);
		}
	}
	if (ft_right_cs_zeroes(tab, a, len) == -1)
		return (-1);
	return (0);
}

static int	ft_right_cs_zeroes(t_print *tab, char *a, int len)
{	
	int	pad;

	if (tab->wdt > len && tab->zero && tab->pnt)
	{
		tab->zero = 0;
		if (ft_right_cs_x(tab, a) == -1)
			return (-1);
		return (0);
	}
	pad = tab->wdt - len;
	if (tab->wdt > len && tab->zero && !tab->pnt)
	{
		if (tab->hash && len == 4)
			pad = tab->wdt - len - 1;
		if (!tab->sign && tab->sp)
			pad = tab->wdt - len;
		if (tab->pnt && ((tab->prc > len && !tab->hash)
				|| ((tab->hash) && (tab->wdt > tab->prc))))
			pad = tab->wdt - tab->prc;
		if (tab->pnt && tab->prc > len && tab->hash && tab->wdt < tab->prc)
			pad = tab->wdt - tab->prc - 2;
		if (upper_x_zeroes_support(tab, pad, len, a) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_left_cs(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	if (len == 0 && tab->wdt == tab->prc)
		pad = 0;
	else
		pad = tab->wdt - len;
	pad = calculate_padding_x_left(tab, a, len, pad);
	if (tab->wdt > len && !tab->zero)
	{
		if (write_padding(tab, pad) == -1)
			return (-1);
	}
	return (0);
}

int	ft_precision_upper(t_print *tab, char *j, size_t i)
{
	if (lower_precision_support(tab, j) == -1)
		return (-1);
	if (j[0] == '0' && j[1] == '\0')
	{
		if (print(tab, j[0]) == -1)
			return (-1);
	}
	else
	{
		while (*j && i != 0)
		{
			if (print(tab, j[i - 1]) == -1)
				return (-1);
			i--;
		}
	}
	if (tab->wdt && tab->dash && tab->wdt >= tab->prc)
	{
		if (ft_left_cs(tab, j) == -1)
			return (-1);
	}
	free(j);
	return (0);
}

int	ft_printf_upper(t_print *tab)
{
	unsigned int	a;
	int				digit;

	a = va_arg(tab->args, unsigned int);
	digit = 0;
	if (ft_printf_x_upper(tab, digit, a) == -1)
		return (-1);
	tab->zero = 0;
	return (0);
}
