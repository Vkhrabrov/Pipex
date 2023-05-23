/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:24:15 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:44 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "../libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

static int	ft_right_cs(t_print *tab)
{
	int	pad;

	pad = 0;
	if (tab->wdt > 1 && !tab->zero)
	{
		pad = tab->wdt - 1;
		while (pad--)
		{
			if (print(tab, ' ') == -1)
				return (-1);
		}
	}
	if (tab->wdt && tab->zero)
	{
		pad = tab->wdt - 1;
		while (pad--)
		{
			if (print(tab, '0') == -1)
				return (-1);
		}
	}
	return (0);
}

static int	ft_left_cs(t_print *tab)
{
	int	pad;

	pad = 0;
	if (tab->wdt > 1)
		pad = tab->wdt - 1;
	while (pad--)
	{
		if (print(tab, ' ') == -1)
			return (-1);
	}
	return (0);
}

int	ft_print_percent(t_print *tab)
{
	if (tab->wdt && !tab->dash)
	{
		if (ft_right_cs(tab) == -1)
			return (-1);
	}
	if (print(tab, '%') == -1)
		return (-1);
	tab->perc = 1;
	if (tab->wdt && tab->dash)
	{
		if (ft_left_cs(tab) == -1)
			return (-1);
	}
	tab->zero = 0;
	tab->dash = 0;
	tab->prc = 0;
	tab->wdt = 0;
	return (0);
}
