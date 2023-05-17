/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:45:50 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/17 22:20:06 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_initialize_tab(t_pipex *tab)
{
	tab->in_fd = -1;
	tab->out_fd = -1;
	tab->here_doc = 0;
	tab->invalid_infile = 0;
	tab->i = 0;
	tab->b = 0;
	tab->delimiter_heredoc = "EOF";
	tab->delimiter = 0;
	tab->path_from_envp = NULL;
	tab->paths = NULL;
	tab->path = NULL;
	tab->cmd = NULL;
	tab->cmd_paths = NULL;
	tab->cmd_args = NULL;
	tab->cmd_count = 0;
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
	line = get_next_line(0);
	while (line != NULL)
	{
		if (ft_strncmp(line, tab->delimiter_heredoc, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		tab->i = 0;
		while (line[tab->i++] != '\0')
			ft_putchar_fd(line[tab->i], pipe_fd[tab->i]);
		ft_putchar_fd('\n', pipe_fd[tab->i]);
		free(line);
	}
	if (close(pipe_fd[tab->i]))
		exit (error_msg(PPX, "open", CNC, clean_exit(tab, 1)));
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
