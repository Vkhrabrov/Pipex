/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:16:49 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/03/29 22:36:55 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_printf_main_add(t_print *tab, const char *format, int i, int total)
{
	tab->tl = total;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			ft_eval_format_bonus(tab, format, i + 1);
			if (ft_eval_conversion(tab, format, tab->pos) == -1)
				return (-1);
			tab->pnt = 0;
			tab->prc = 0;
			tab->wdt = 0;
			tab->dash = 0;
			tab->is_zero = 0;
			i++;
			while (format[i] && !ft_is_valid_specifier(format[i]))
				i++;
		}
		else
		{
			if (print(tab, format[i]) == -1)
				return (-1);
		}
	}
	return (0);
}
