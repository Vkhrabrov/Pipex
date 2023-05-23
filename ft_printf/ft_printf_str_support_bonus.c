/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_support_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:30:44 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:37:25 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_printf.h"

int			print_hash(t_print *tab, int len, int *pad);
int			print_hash_left(t_print *tab, int len, int *pad);
int			ft_apply_padding(t_print *tab, int pad);
int			ft_is_hash_condition(char *a, int len, int pad);

int	str_support(t_print *tab, char *a, size_t i)
{
	while (a[i] && i < (size_t)tab->prc)
	{
		if (print(tab, a[i++]) == -1)
			return (-1);
	}
	return (0);
}

int	lower_x_zeroes_support(t_print *tab, int pad, int len, char *a)
{
	if (!tab->pnt && tab->hash && ft_is_hash_condition(a, len, pad))
	{
		if (print_hash(tab, len, &pad) == -1)
			return (-1);
	}
	if (ft_apply_padding(tab, pad) == -1)
		return (-1);
	return (0);
}

int	upper_x_zeroes_support(t_print *tab, int pad, int len, char *a)
{
	if (!tab->pnt && tab->hash && ft_is_hash_condition(a, len, pad))
	{
		if (print_hash_left(tab, len, &pad) == -1)
			return (-1);
	}
	if (ft_apply_padding(tab, pad) == -1)
		return (-1);
	return (0);
}

int	lower_precision_support(t_print *tab, char *j)
{
	size_t	k;

	k = 0;
	if (tab->pnt && (size_t)tab->prc > ft_strlen(j))
	{
		k = tab->prc - ft_strlen(j);
		while (k--)
		{
			if (print(tab, '0') == -1)
				return (-1);
		}
	}
	return (0);
}
