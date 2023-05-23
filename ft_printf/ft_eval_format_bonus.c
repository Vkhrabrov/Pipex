/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_format_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:37:14 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:53 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void	ft_tab_fill_next(t_print *tab, const char *format, int pos)
{
	tab->pos = pos;
	while (ft_strchr("cspdiuxX%", format[tab->pos]) == NULL)
	{
		if (format[tab->pos] == ' ')
			tab->sp = 1;
		if (format[tab->pos] == '#')
			tab->hash = 1;
		if (format[tab->pos] == '+')
			tab->sign = 1;
		tab->pos++;
	}
}

int	ft_tab_fill(t_print *tab, const char *format, int pos, int i)
{
	tab->pos = pos;
	while (ft_strchr("cspdiuxX%", format[tab->pos]) == NULL)
	{
		if (format[tab->pos] >= '0' && format[tab->pos] <= '9')
			i = i * 10 + format[tab->pos] - '0';
		if (format[tab->pos] == '.')
		{
			tab->wdt = i;
			i = 0;
			tab->pnt = 1;
		}
		if (format[tab->pos] == '-')
			tab->dash = 1;
		if (format[tab->pos] == '0' && (format[tab->pos - 1] == '%'
				|| format[tab->pos - 1] == ' ' || format[tab->pos - 1] == '+'
				|| format[tab->pos - 1] == '#'))
			tab->zero = 1;
		tab->pos++;
	}
	ft_tab_fill_next(tab, format, pos);
	return (i);
}

void	ft_eval_format_bonus(t_print *tab, const char *format, int pos)
{
	int	i;

	i = 0;
	i = ft_tab_fill(tab, format, pos, i);
	if (tab->pnt != 0)
		tab->prc = i;
	else
		tab->wdt = i;
}
