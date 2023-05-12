/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:44:00 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/04/02 21:07:46 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include<stddef.h>
# include<stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_print
{
	va_list	args;
	int		wdt;
	int		prc;
	int		zero;
	int		pnt;
	int		dash;
	int		tl;
	int		sign;
	int		is_zero;
	int		perc;
	int		sp;
	int		hash;
	int		pos;
	int		minus;
}			t_print;
int			unsigned_int_support(t_print *tab, char *j, unsigned int a);
int			str_support(t_print *tab, char *a, size_t i);
int			print_int_support(t_print *tab, char *j);
int			ft_right_cs_int(t_print *tab, char *a);
int			print(t_print *tab, char c);
int			write_padding_x(t_print *tab, int pad);
int			calculate_padding_x(t_print *tab, char *a, int len);
int			empty_string(char **j);
void		calculate_left_padding(t_print *tab, char *a, int len, int *pad);
int			ft_zero_pad(t_print *tab, char *a, int len);
int			write_padding(t_print *tab, int pad);
void		calculate_padding(t_print *tab, char *a, int len, int *pad);
int			ft_printf(const char *format, ...);
int			ft_print_char(t_print *tab);
int			ft_print_string(t_print *tab);
int			ft_print_pointer(t_print *tab);
int			ft_print_int(t_print *tab);
int			ft_print_unsigned_int(t_print *tab);
char		*ft_utoa(unsigned int n);
int			ft_print_lower(t_print *tab);
int			ft_print_upper(t_print *tab);
int			ft_print_percent(t_print *tab);
int			ft_printf_main_add(t_print *tab,
				const char *format, int i, int total);
int			ft_is_valid_specifier(char c);
void		ft_eval_format_bonus(t_print *tab, const char *format, int pos);
int			ft_eval_conversion(t_print *tab, const char *format, int pos);
int			ft_printf_unsigned_int(t_print *tab);
int			ft_printf_lower(t_print *tab);
int			ft_printf_x_lower(t_print *tab, int digit,
				unsigned int a);
int			ft_printf_x_upper(t_print *tab, int digit,
				unsigned int a);
int			ft_right_cs_x(t_print *tab, char *a);
int			ft_printf_upper(t_print *tab);
#endif