/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:47:05 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/16 23:51:58 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char findFirstDelimiter(const char *str, const char *delimiters) 
{
    while (*str) {
        if (ft_strchr(delimiters, *str)) {
            return *str;
        }
        str++;
    }
    return '\0';
}

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