/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:35:01 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/18 21:31:53 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	extra_clean_exit(t_pipex *tab)
{
	size_t	iter;

	iter = 0;
	if (tab->cmd_args)
	{
		while (tab->cmd_args[iter])
			free(tab->cmd_args[iter++]);
		free(tab->cmd_args);
	}
}

int	clean_exit(t_pipex *tab, int ret)
{
	size_t	iter;

	if (tab->in_fd)
		close(tab->in_fd);
	if (tab->out_fd)
		close(tab->out_fd);
	if (tab->paths)
	{
		iter = 0;
		while (tab->paths[iter])
			free(tab->paths[iter++]);
		free(tab->paths);
	}
	if (tab->path_from_envp)
		free(tab->path_from_envp);
	extra_clean_exit(tab);
	free(tab);
	return (ret);
}

int	error_msg(char *first, char *second, char *thrd, int ret)
{
	size_t	len;

	if (!first)
		len = 0;
	else
		len = ft_strlen(first);
	write(2, first, len);
	write(2, second, ft_strlen(second));
	write(2, thrd, ft_strlen(thrd));
	write(2, "\n", 1);
	return (ret);
}