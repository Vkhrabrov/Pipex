/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_lower_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:01:12 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:09 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "../libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_precision(t_print *tab, char *j, size_t i);
int	ft_right_cs_x(t_print *tab, char *a);
int	ft_tabs_precisions(t_print *tab, char *j, size_t i);

static int	ft_size(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

int	ft_printf_x_lower(t_print *tab, int digit, unsigned int a)
{
	char	*hex_digits;
	size_t	i;
	char	*j;

	i = 0;
	hex_digits = "0123456789abcdef";
	j = (char *)malloc(sizeof(char) * (ft_size(a) + 1));
	if (!j)
		return (-1);
	if (a == 0 && !tab->pnt)
		j[i++] = '0';
	while (a > 0)
	{
		digit = a % 16;
		j[i++] = hex_digits[digit];
		a /= 16;
	}
	j[i] = '\0';
	if (ft_tabs_precisions(tab, j, i) == -1)
	{
		free(j);
		return (-1);
	}
	return (0);
}

int	ft_tabs_precisions(t_print *tab, char *j, size_t i)
{
	if (tab->wdt && !tab->dash && tab->wdt > tab->prc)
	{
		if (ft_right_cs_x(tab, j) == -1)
			return (-1);
	}
	if (i > 0)
	{
		if (!tab->is_zero && tab->hash && j[i - 1] != '0')
		{
			if (print(tab, '0') == -1)
				return (-1);
			if (print(tab, 'x') == -1)
				return (-1);
		}
	}	
	if (ft_precision(tab, j, i) == -1)
		return (-1);
	return (0);
}
