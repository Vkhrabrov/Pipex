/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:04:28 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/03/31 01:30:26 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

int	ft_print_string_2(t_print *tab, char *a, size_t i);
int	strint_right_cs_support(t_print *tab, int pad);
int	str_support(t_print *tab, char *a, size_t i);

static int	ft_right_cs(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	pad = 0;
	if (tab->prc < len && tab->pnt)
		len = tab->prc;
	if (tab->wdt > len)
		pad = tab->wdt - len;
	if (strint_right_cs_support(tab, pad) == -1)
		return (-1);
	return (0);
}

static int	ft_left_cs(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	pad = 0;
	if (tab->prc < len && tab->pnt)
		len = tab->prc;
	if (tab->wdt > len)
		pad = tab->wdt - len;
	while (pad--)
	{
		if (print(tab, ' ') == -1)
			return (-1);
	}
	return (0);
}

int	ft_print_string(t_print *tab)
{
	char	*a;
	size_t	i;

	i = 0;
	a = va_arg(tab->args, char *);
	if (a == NULL)
		a = "(null)";
	if (tab->pnt != 0)
	{
		if (tab->wdt && !tab->dash)
		{
			if (ft_right_cs(tab, a) == -1)
				return (-1);
		}
		if (str_support(tab, a, i) == -1)
			return (-1);
		if (tab->wdt && tab->dash)
		{
			if (ft_left_cs(tab, a) == -1)
				return (-1);
		}
	}
	if (ft_print_string_2(tab, a, i) == -1)
		return (-1);
	return (0);
}

int	ft_print_string_2(t_print *tab, char *a, size_t i)
{
	if (tab->pnt == 0)
	{
		if (tab->wdt && !tab->dash)
		{
			if (ft_right_cs(tab, a) == -1)
				return (-1);
		}
		while (*a && i < ft_strlen(a))
		{
			if (print(tab, a[i]) == -1)
				return (-1);
			i++;
		}
		if (tab->wdt && tab->dash)
		{
			if (ft_left_cs(tab, a) == -1)
				return (-1);
		}
	}
	tab->dash = 0;
	tab->zero = 0;
	tab->wdt = 0;
	return (0);
}
