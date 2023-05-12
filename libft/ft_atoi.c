/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:51:01 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/01/28 21:39:27 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	sign_count;

	i = 0;
	j = 1;
	sign_count = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			j = j * -1;
		str++;
		sign_count++;
	}
	if (sign_count > 1)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + *str - '0';
	str++;
	}
	return (i * j);
}
