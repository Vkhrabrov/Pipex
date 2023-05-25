/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:35:45 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/25 18:42:45 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	string_parsing_back_slashes(t_pipex *tab, char *argv)
{
	tab->i = 0;
	tab->delimiter = find_first_delimiter(argv, "\'\"");
	tab->b = 0;
	while (argv[tab->i] != '\0')
	{
		if (argv[tab->i] == '\"')
			tab->b++;
		tab->i++;
	}
	if (tab->b % 2 != 0)
	{
		tab->delimiter = '\0';
		argv = removing_char(argv, '\\');
	}
	else
	{
		tab->b = 0;
		while (argv[tab->b++] != '\0')
		{
			if (argv[tab->b] == '\\' && argv[tab->b + 1] == '\"')
				argv[tab->b + 1] = '\'';
		}
	}
	tab->b = 0;
	string_parsing_quotes(tab, argv);
}

void	string_parsing_quotes(t_pipex *tab, char *argv)
{
	if (tab->delimiter != '\0')
	{
		tab->cmd_args = ft_split(argv, tab->delimiter);
		while (tab->cmd_args[1][tab->b++] != '\0')
		{
			if (tab->cmd_args[1][tab->b] == '\\'
				&& tab->cmd_args[1][tab->b + 1] == '\'')
				tab->cmd_args[1][tab->b + 1] = '\"';
		}
		tab->cmd_args[1] = removing_char(tab->cmd_args[1], '\\');
		tab->cmd_args[0] = removing_char(tab->cmd_args[0], ' ');
	}
	else
		tab->cmd_args = ft_split(argv, ' ');
	tab->i = 0;
	if (tab->cmd_args[0][0] == '/' || tab->cmd_args[0][0] == '.' ||
			ft_strrchr(tab->cmd_args[0], '/') != NULL)
	{
		tab->cmd = ft_strdup(tab->cmd_args[0]);
		if (access(tab->cmd, X_OK) != 0)
			exit(error_msg(PPX, tab->cmd_args[0], CNF, 126));
		return ;
	}
	string_parsing_final(tab);
}

int	string_parsing_final(t_pipex *tab)
{
	tab->i = 0;
	while (tab->paths[tab->i])
	{
		tab->cmd_paths = ft_strjoin(tab->paths[tab->i], "/");
		tab->cmd = ft_strjoin(tab->cmd_paths, tab->cmd_args[0]);
		if (access(tab->cmd, X_OK) == 0)
			return (0);
		free(tab->cmd);
		tab->i++;
	}
	exit(error_msg(PPX, tab->cmd_args[0], CNF, 127));
}

void	check_path(t_pipex *tab, char *argv, char *envp[])
{
	if (envp)
	{
		while (envp[tab->i])
		{
			if (ft_strncmp(envp[tab->i], "PATH=", 5) == 0)
			{
				tab->path = ft_substr(envp[tab->i], 5,
						ft_strlen(envp[tab->i]) - 5);
				break ;
			}
			tab->i++;
		}
	}
	check_path_part_2(tab, argv);
}

void	check_path_part_2(t_pipex *tab, char *argv)
{
	if (tab->path)
	{
		tab->path_from_envp = tab->path;
		tab->paths = ft_split(tab->path_from_envp, ':');
		if (!tab->paths)
			exit(error_msg(NULL, "bash", MKO, clean_exit(tab, 1)));
	}
	else
	{
		tab->paths = ft_split(DEFPATH, ':');
		if (!tab->paths)
			exit(error_msg(NULL, "bash", MKO, clean_exit(tab, 1)));
	}
	string_parsing_back_slashes(tab, argv);
}
