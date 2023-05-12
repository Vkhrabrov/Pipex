/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:04:15 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/13 01:19:35 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

t_print	*ft_initialize_tab(t_print *tab)
{
	tab->wdt = 0;
	tab->prc = 0;
	tab->zero = 0;
	tab->pnt = 0;
	tab->dash = 0;
	tab->tl = 0;
	tab->sign = 0;
	tab->is_zero = 0;
	tab->perc = 0;
	tab->sp = 0;
	tab->hash = 0;
	tab->pos = 0;
	tab->minus = 0;
	return (tab);
}

int	ft_eval_conversion(t_print *tab, const char *format, int pos)
{
	if (format[pos] == 'c')
		return (ft_print_char(tab));
	else if (format[pos] == 's')
		return (ft_print_string(tab));
	else if (format[pos] == 'p')
		return (ft_print_pointer(tab));
	else if (format[pos] == 'd' || format[pos] == 'i')
		return (ft_print_int(tab));
	else if (format[pos] == 'u')
		return (ft_printf_unsigned_int(tab));
	else if (format[pos] == 'x')
		return (ft_printf_lower(tab));
	else if (format[pos] == 'X')
		return (ft_printf_upper(tab));
	else if (format[pos] == '%')
		return (ft_print_percent(tab));
	return (0);
}

int	ft_is_valid_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		ret;
	t_print	*tab;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	ft_initialize_tab(tab);
	i = -1;
	if (format)
	{
		va_start(tab->args, format);
		if (ft_printf_main_add(tab, format, i, tab->tl) == -1)
		{
			free(tab);
			return (-1);
		}
		va_end(tab->args);
	}
	ret = tab->tl;
	free(tab);
	return (ret);
}

int	main(void)
{
	int		i;
	int		j;
	void	*ncm_p;
	void	*ptr2;

	ncm_p = malloc(sizeof(int));
	ptr2 = malloc(sizeof(int));
	i = ft_printf(" %c %c %c ", '0', 0, '1');
	printf("The number of characters: %i\n", i);
	j = printf(" %c %c %c ", '0', 0, '1');
	printf("The number of characters: %i\n", j);
	return (0);
}
