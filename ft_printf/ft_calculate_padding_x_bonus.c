/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_padding_x.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:50:59 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/03/30 19:41:59 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "libft/libft.h"

int	calculate_padding_x(t_print *tab, char *a, int len)
{
	int	pad;

	pad = tab->wdt - len;
	if (!tab->sign && tab->sp)
		pad = tab->wdt - len;
	if (tab->pnt && ((tab->prc > len && !tab->hash) || ((tab->hash)
				&& (tab->wdt > tab->prc))))
		pad = tab->wdt - tab->prc;
	if (tab->pnt && tab->prc > len && tab->hash && tab->wdt < tab->prc)
		pad = tab->wdt - tab->prc - 2;
	if (!tab->pnt && tab->hash && ((a[0] != '0') || (len > 1)))
		pad = tab->wdt - len - 2;
	if (tab->pnt && tab->hash && tab->prc < len)
		pad = tab->wdt - len - 2;
	if (tab->prc < len && !tab->hash)
		pad = tab->wdt - len;
	if (tab->prc && tab->hash && tab->wdt > tab->prc && tab->prc == len
		&& len == 1)
		pad = tab->wdt - tab->prc - 2;
	if (a[0] != 0 && tab->prc && tab->hash && tab->wdt > tab->prc
		&& tab->prc >= len)
		pad = tab->wdt - tab->prc - 2;
	if (pad < 0)
		pad = 0;
	return (pad);
}

int	print_hash(t_print *tab, int len, int *pad)
{
	tab->is_zero = 1;
	if (print(tab, '0') == -1)
		return (-1);
	if (print(tab, 'x') == -1)
		return (-1);
	*pad = tab->wdt - len - 2;
	return (0);
}

int	ft_apply_padding(t_print *tab, int pad)
{
	if (pad < 0)
		pad = 0;
	while (pad--)
	{
		if (print(tab, '0') == -1)
			return (-1);
	}
	return (0);
}

int	ft_is_hash_condition(char *a, int len, int pad)
{
	return ((len == 1 && a[0] != '0') || (pad != 0 && a[0] != '0')
		|| (a[0] == '0' && len > 1));
}

int	calculate_padding_x_left(t_print *tab, char *a, int len, int pad)
{
	if (!tab->sign && tab->sp)
		pad = tab->wdt - len;
	if (tab->pnt && ((tab->prc > len && !tab->hash)
			|| (tab->hash && tab->wdt >= tab->prc)))
		pad = tab->wdt - tab->prc;
	if (tab->pnt && tab->prc > len && tab->hash && tab->wdt < tab->prc)
		pad = tab->wdt - tab->prc - 2;
	if (!tab->pnt && tab->hash && ((a[0] != '0') || (len > 1)))
		pad = tab->wdt - len - 2;
	if (tab->pnt && tab->hash && tab->prc < len)
		pad = tab->wdt - len - 2;
	if ((tab->prc < len && !tab->hash))
		pad = tab->wdt - len;
	if (tab->prc && tab->hash && tab->wdt > tab->prc && tab->prc == len
		&& len == 1)
		pad = tab->wdt - tab->prc - 2;
	if (a[0] != 0 && tab->prc && tab->hash && tab->wdt > tab->prc
		&& tab->prc >= len)
		pad = tab->wdt - tab->prc - 2;
	if (pad < 0)
		pad = 0;
	return (pad);
}
