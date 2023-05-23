/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int_support_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:44:54 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:35 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_printf.h"

int	ft_right_cs_int(t_print *tab, char *a);

int	print_int_support(t_print *tab, char *j)
{
	if (tab->wdt && !tab->dash && tab->wdt >= tab->prc)
	{
		if (ft_right_cs_int(tab, j) == -1)
			return (-1);
	}
	if (j[0] == '-' && tab->zero && ((tab->wdt < tab->prc)
			|| (!tab->wdt && !tab->prc)))
		if (print(tab, '-') == -1)
			return (-1);
	if (j[0] == '-' && !tab->zero)
	{
		if (print(tab, '-') == -1)
			return (-1);
	}
	if (!tab->is_zero && tab->sign && !(j[0] == '-'))
	{
		if (print(tab, '+') == -1)
			return (-1);
	}
	if (!tab->is_zero && !tab->sign && tab->sp && !tab->zero && j[0] != '-')
	{
		if (print(tab, ' ') == -1)
			return (-1);
	}
	return (0);
}

int	int_precision_support(t_print *tab, char *j, size_t i, size_t k)
{
	if (!tab->is_zero && !tab->sign && tab->sp && tab->zero && j[i] != '-')
	{
		if (print(tab, ' ') == -1)
			return (-1);
	}
	if (tab->pnt && (size_t)tab->prc > ft_strlen(j) - 1)
	{
		if (j[i] == '-')
			k = tab->prc - ft_strlen(j) + 1;
		else
			k = tab->prc - ft_strlen(j);
		while (k--)
		{
			if (print(tab, '0') == -1)
				return (-1);
		}
	}
	return (0);
}

int	int_zeroes_support(t_print *tab, char *a)
{
	if (a[0] == '-' && tab->zero)
	{
		if (print(tab, '-') == -1)
			return (-1);
	}
	if (!tab->sign && tab->sp && a[0] != '-' && tab->wdt != tab->prc)
	{
		tab->is_zero = 1;
		if (print(tab, ' ') == -1)
			return (-1);
	}
	if (tab->sign && !tab->sp && a[0] != '-' && tab->wdt != tab->prc)
	{
		tab->is_zero = 1;
		if (print(tab, '+') == -1)
			return (-1);
	}
	return (0);
}

int	pointer_support(t_print *tab, char *buffer, int digit, int j)
{
	if (print(tab, buffer[0]) == -1)
		return (-1);
	if (print(tab, buffer[1]) == -1)
		return (-1);
	if (digit == 0)
	{
		if (print(tab, '0') == -1)
			return (-1);
	}
	else if (digit != 0)
	{
		j = ft_strlen(buffer) - 1;
		while (*buffer && j >= 2)
		{	
			if (print(tab, buffer[j]) == -1)
				return (-1);
			j--;
		}
	}
	return (0);
}

int	strint_right_cs_support(t_print *tab, int pad)
{
	if (tab->zero == 0)
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
