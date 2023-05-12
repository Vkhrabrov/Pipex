/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:47:02 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/03/31 01:29:40 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

int	ft_print_pointer_second_part(t_print *tab, char *buffer, int digit);
int	pointer_support(t_print *tab, char *buffer, int digit, int j);

static int	ft_update_buffer(t_print *tab, char *buffer,
				int digit, unsigned long address)
{
	int		i;
	char	*hex_digits;

	i = 2;
	hex_digits = "0123456789abcdef";
	if (address == 0)
	{
		buffer[2] = '0';
		buffer[3] = '\0';
	}
	else
	{
		while (address > 0)
		{
			digit = address % 16;
			buffer[i++] = hex_digits[digit];
			address /= 16;
		}
		buffer[i] = '\0';
	}
	if (ft_print_pointer_second_part(tab, buffer, digit) == -1)
		return (-1);
	return (0);
}

static int	ft_right_cs(t_print *tab, char *a)
{
	int	len;
	int	pad;

	len = ft_strlen(a);
	pad = 0;
	if (tab->wdt > len)
		pad = tab->wdt - len;
	while (pad--)
	{
		if (print(tab, ' ') == -1)
			return (-1);
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
		pad = tab->wdt - len;
	while (pad--)
	{
		if (print(tab, ' ') == -1)
			return (-1);
	}
	return (0);
}

int	ft_print_pointer(t_print *tab)
{
	unsigned long	address;
	char			*hex_digits;
	char			buffer[20];
	int				i;
	int				digit;

	i = 2;
	digit = 0;
	hex_digits = "0123456789abcdef";
	buffer[0] = '0';
	buffer[1] = 'x';
	address = (unsigned long)va_arg(tab->args, void *);
	if (ft_update_buffer(tab, buffer, digit, address) == -1)
		return (-1);
	return (0);
}

int	ft_print_pointer_second_part(t_print *tab, char *buffer, int digit)
{
	int	j;

	j = 0;
	if (tab->wdt && !tab->dash)
	{
		if (ft_right_cs(tab, buffer) == -1)
			return (-1);
	}
	if (pointer_support(tab, buffer, digit, j) == -1)
		return (-1);
	if (tab->wdt && tab->dash && tab->wdt >= tab->prc)
	{
		if (ft_left_cs(tab, buffer) == -1)
			return (-1);
	}
	return (0);
}
