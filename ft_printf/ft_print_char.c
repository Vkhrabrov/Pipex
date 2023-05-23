/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:04:51 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:50 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "../libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

void	ft_update_tab(t_print *tab, int value)
{
	tab->tl += value;
}

int	ft_right_cs(t_print *tab)
{
	int	pad;

	pad = tab->wdt - 1;
	if (!tab->zero)
	{
		while (pad--)
		{
			if (print(tab, ' ') == -1)
				return (-1);
		}
	}
	else
	{
		while (pad--)
		{
			if (print(tab, '0') == -1)
				return (-1);
		}
	}
	return (0);
}

int	ft_left_cs(t_print *tab)
{
	int	pad;

	pad = tab->wdt - 1;
	while (pad--)
	{
		if (print(tab, ' ') == -1)
			return (-1);
	}
	return (0);
}

int	ft_print_char(t_print *tab)
{
	char	a;

	a = va_arg(tab->args, int);
	if (tab->wdt && !tab->dash)
	{
		if (ft_right_cs(tab) == -1)
			return (-1);
	}
	if (print(tab, a) == -1)
		return (-1);
	if (tab->wdt && tab->dash)
	{
		if (ft_left_cs(tab) == -1)
			return (-1);
	}
	tab->dash = 0;
	tab->zero = 0;
	return (0);
}
