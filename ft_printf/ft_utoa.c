/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:25:23 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/22 23:36:50 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "../libft/libft.h"

static char	*ft_string(char *str, int i, unsigned int n)
{
	while (n != 0)
	{
		str[--i] = (char)(n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

static int	ft_size(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_utoa(unsigned int n)
{
	unsigned int	i;
	char			*str;

	i = ft_size(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (str);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str[i] = '\0';
	str = ft_string(str, i, n);
	return (str);
}
