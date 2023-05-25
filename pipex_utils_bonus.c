/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:34:07 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/25 18:57:37 by vkhrabro         ###   ########.fr       */
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
	tab->d_hd = NULL;
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
	tab->line = NULL;
	tab->num_lines = 0;
	tab->lines = NULL;
	tab->temp = NULL;
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

void	creating_lines_heredoc(t_pipex *tab)
{
	tab->lines = malloc(sizeof(char *));
	if (!tab->lines)
		exit (clean_exit(tab, 1));
	ft_putstr_fd("pipex here_doc> ", 1);
	tab->line = get_next_line(0);
	if (tab->line[0] == '\n')
		tab->line[0] = '\0';
	while (tab->line)
	{
		if (ft_strncmp(tab->line, tab->d_hd, ft_strlen(tab->d_hd)) == 0
			&& ft_strlen(tab->line) == ft_strlen(tab->d_hd))
		{
			free(tab->line);
			break ;
		}
		tab->lines[tab->num_lines] = tab->line;
		tab->num_lines++;
		tab->temp = malloc(sizeof(char *) * (tab->num_lines + 1));
		if (!tab->temp)
			exit (clean_exit(tab, 1));
		memcpy(tab->temp, tab->lines, sizeof(char *) * tab->num_lines);
		free(tab->lines);
		tab->lines = tab->temp;
		tab->line = get_next_line(0);
	}
}

int	parsing_here_doc(t_pipex *tab)
{
	int		pipe_fd[2];

	tab->i = 0;
	if (pipe(pipe_fd) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(tab, 1)));
	creating_lines_heredoc(tab);
	if (tab->num_lines > 0 && tab->lines[tab->num_lines - 1][0] == '\n')
		tab->lines[tab->num_lines - 1][0] = '\0';
	while (tab->b < tab->num_lines)
	{
		tab->i = 0;
		while (tab->lines[tab->b][tab->i] != '\0')
		{
			ft_putchar_fd(tab->lines[tab->b][tab->i], pipe_fd[1]);
			tab->i++;
		}
		free(tab->lines[tab->b]);
		tab->b++;
	}
	free(tab->lines);
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
