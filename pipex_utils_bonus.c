/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:34:07 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/24 01:31:55 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialize_tab(t_pipex *tab)
{
	tab->in_fd = -1;
	tab->out_fd = -1;
	tab->here_doc = 0;
	tab->invalid_infile = 0;
	tab->i = 0;
	tab->b = 0;
	tab->delimiter_heredoc = NULL;
	tab->delimiter = 0;
	tab->path_from_envp = NULL;
	tab->paths = NULL;
	tab->path = NULL;
	tab->cmd = NULL;
	tab->cmd_paths = NULL;
	tab->cmd_args = NULL;
	tab->cmd_count = 0;
	tab->argc_tab = 0;
	tab->heredoc = 0;
}

char	find_first_delimiter(const char *str, const char *delimiters)
{
	while (*str)
	{
		if (ft_strchr(delimiters, *str))
			return (*str);
		str++;
	}
	return ('\0');
}

int	parsing_here_doc(t_pipex *tab)
{
	char	*line;
	int		pipe_fd[2];

	tab->i = 0;
	line = NULL;
	if (pipe(pipe_fd) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(tab, 1)));
	ft_putstr_fd("pipex here_doc> ", 1);
	line = get_next_line(0);
	if (line[0] == '\n')
		line[0] = '\0';
	if (!line)
		exit(clean_exit(tab, 0));
	while (line != NULL)
	{
		if (ft_strncmp(line, tab->delimiter_heredoc, ft_strlen(tab->delimiter_heredoc)) == 0 
			&& ft_strlen(line) == ft_strlen(tab->delimiter_heredoc))
		{
			free(line);
			break ;
		}
		tab->i = 0;
		while (line[tab->i] != '\0')
		{
			ft_putchar_fd(line[tab->i], pipe_fd[1]);
			tab->i++;
		}
		free(line);
		line = get_next_line(0);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}



char	*removing_char(char *cmd, char delimiter)
{
	char	*s1;
	char	*s2;

	s1 = (char *)malloc(ft_strlen(cmd) + 1);
	if (!s1)
		return (NULL);
	s2 = s1;
	while (*cmd != '\0')
	{
		if (*cmd != delimiter)
			*s1++ = *cmd;
		cmd++;
	}
	*s1 = '\0';
	return (s2);
}