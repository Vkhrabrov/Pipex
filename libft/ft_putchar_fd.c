/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:34:54 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/02/07 20:36:25 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*int fd;

fd = open("myfile.txt", WR_C);
if(fd == -1){
	write(2, "Error: ocant open the file", 35
	return(NULL)
}
ft_putchar_fd('a', fd);

close(fd);

int ret;
ret = printf("something");
if(return == -1)
	write(2, "ERROR: printf can t write");

ret = write(1, "hello", 4);
if(ret == -1)

STDIN
FD - 0 -> STDIN
FD = 1 -> STDOUT -> screen	
FD = 2 - > STDERR -> screen but also is computed like an error
FD = 3 -> myfile.txt*/
