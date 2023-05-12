/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_padding_left_int.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:59:35 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/04/02 20:54:32 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include <stdlib.h>
#include "libft/libft.h"

void	calculate_left_padding(t_print *tab, char *a, int len, int *pad)
{
	if (tab->wdt > len)
	{
		*pad = tab->wdt - len;
		if ((tab->sign || tab->sp) && tab->wdt == tab->prc)
			*pad = 0;
		if ((tab->sp || tab->sign) && tab->wdt < tab->prc && tab->prc < len)
			*pad = tab->wdt - len - 1;
		if ((tab->sp || tab->sign) && tab->wdt > tab->prc && a[0] == '-'
			&& tab->prc < len)
			*pad = tab->wdt - len;
		if ((tab->sp || tab->sign) && tab->wdt > tab->prc && a[0] != '-'
			&& tab->prc < len)
			*pad = tab->wdt - len - 1;
		if ((tab->sign || tab->sp) && tab->wdt != tab->prc && tab->pnt != 0
			&& tab->prc >= len)
			*pad = tab->wdt - tab->prc - 1;
		if (!tab->sign && !tab->sp && tab->pnt != 0 && a[0] != '-'
			&& tab->prc > len)
			*pad = tab->wdt - tab->prc;
		if ((!tab->sp && !tab->sign) && tab->pnt != 0 && a[0] == '-')
			*pad = tab->wdt - tab->prc - 1;
		if (!tab->sp && !tab->sign && tab->prc < len)
			*pad = tab->wdt - len;
	}
}

int	empty_string(char **j)
{
	free(*j);
	*j = ft_strdup("");
	if (!*j)
		return (-1);
	return (0);
}

int	print_hash_left(t_print *tab, int len, int *pad)
{
	tab->is_zero = 1;
	if (print(tab, '0') == -1)
		return (-1);
	if (print(tab, 'X') == -1)
		return (-1);
	*pad = tab->wdt - len - 2;
	return (0);
}

int	tab_return(t_print *tab, char *a)
{
	tab->zero = 0;
	if (ft_right_cs_int(tab, a) == -1)
		return (-1);
	return (0);
}
