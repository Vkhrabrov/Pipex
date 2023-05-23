/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_int_support_bonus.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:23:23 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:39:01 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include <stdlib.h>
#include "../libft/libft.h"

int	ft_right_cs_unsigned_int(t_print *tab, char *a);
int	ft_precision_unsigned_int(t_print *tab, char *j, size_t i);

int	handle_zero_case(t_print *tab, char **j, unsigned int a)
{
	if (tab->pnt && !tab->prc && a == 0)
	{
		free(*j);
		*j = ft_strdup("");
		if (!*j)
			return (-1);
	}
	return (0);
}

int	ft_printf_unsigned_int_helper(t_print *tab, char *j, unsigned int a)
{
	size_t	i;

	i = 0;
	if (handle_zero_case(tab, &j, a) == -1)
		return (-1);
	if (tab->wdt && !tab->dash && tab->wdt >= tab->prc)
	{
		if (ft_right_cs_unsigned_int(tab, j) == -1)
		{
			free(j);
			return (-1);
		}
	}
	if (ft_precision_unsigned_int(tab, j, i) == -1)
	{
		free(j);
		return (-1);
	}
	free(j);
	return (0);
}
