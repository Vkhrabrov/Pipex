/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:47:01 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/01/27 19:42:27 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>

void	*ft_memset(void *ptr, int x, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n--)
	{
		*p = (unsigned char)x;
		p++;
	}
	return (ptr);
}
