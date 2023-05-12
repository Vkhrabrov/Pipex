/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:27:37 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/04/02 01:25:15 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_right_cs_zeroes(t_print *tab, char *a,
				int len);
int			tab_return(t_print *tab, char *a);
int			print_int_support(t_print *tab, char *j);
int			int_precision_support(t_print *tab, char *j, size_t i, size_t k);
int			int_zeroes_support(t_print *tab, char *a);

int	ft_right_cs_int(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	pad = 0;
	calculate_padding(tab, a, len, &pad);
	if (write_padding(tab, pad) == -1)
		return (-1);
	if (ft_right_cs_zeroes(tab, a, len) == -1)
		return (-1);
	return (0);
}

static int	ft_right_cs_zeroes(t_print *tab, char *a, int len)
{
	if (tab->wdt != tab->prc && tab->wdt > len && tab->zero && tab->pnt)
	{
		if (tab_return(tab, a) == -1)
			return (-1);
		else
			return (0);
	}
	if (int_zeroes_support(tab, a) == -1)
		return (-1);
	if (ft_zero_pad(tab, a, len) == -1)
		return (-1);
	return (0);
}

static int	ft_left_cs(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	pad = 0;
	calculate_left_padding(tab, a, len, &pad);
	if (write_padding(tab, pad) == -1)
		return (-1);
	return (0);
}

static int	ft_precision(t_print *tab, char *j, size_t i)
{
	size_t	k;

	k = 0;
	if (int_precision_support(tab, j, i, k) == -1)
		return (-1);
	if (j[i] == '-')
		i++;
	while (j[i])
	{
		if (print(tab, j[i]) == -1)
			return (-1);
		i++;
	}
	if (tab->wdt && tab->dash && tab->wdt >= tab->prc
		&& (!(tab->wdt == tab->prc && (size_t)tab->prc > ft_strlen(j))))
	{
		if (ft_left_cs(tab, j) == -1)
			return (-1);
	}
	return (0);
}

int	ft_print_int(t_print *tab)
{
	size_t	i;
	char	*j;
	int		a;

	i = 0;
	a = va_arg(tab->args, int);
	j = ft_itoa(a);
	if (!j)
		return (-1);
	if (tab->pnt && !tab->prc && a == 0)
	{
		if (empty_string(&j) == -1)
			return (-1);
	}
	if ((print_int_support(tab, j) == -1) || (ft_precision(tab, j, i) == -1))
	{	
		free(j);
		return (-1);
	}
	tab->zero = 0;
	free(j);
	return (0);
}
