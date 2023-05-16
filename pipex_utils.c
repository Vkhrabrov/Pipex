/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:45:50 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/16 23:56:44 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_initialize_tab(t_pipex *tab)
{
    tab->in_fd = -1;
    tab->out_fd = -1;
    tab->here_doc = 0;
    tab->invalid_infile = 0;
    tab->path_from_envp = NULL;
    tab->paths = NULL;
    tab->cmd = NULL;
    tab->cmd_paths = NULL;
    tab->cmd_args = NULL;
    tab->cmd_count = 0;
}

int ft_check_path(t_pipex *tab, char *argv, char *envp[])
{
    int i;
    char delimiter;
    char *path;

    i = 0;
    path = NULL;
    if(envp)
    {
        while(envp[i])
        {
            if  (ft_strncmp(envp[i], "PATH=", 5) == 0)
            {
                path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
                break;
            } 
        i++;
        }
    }
    if (path)
    {
        tab->path_from_envp = path;
        tab->paths = ft_split(tab->path_from_envp, ':');
        if(!tab->paths)
            exit(error_msg(NULL, "bash", MKO, clean_exit(tab, 1)));
    }
    else
    { 
        tab->paths = ft_split(DEFPATH, ':');
        if (!tab->paths)
            exit (error_msg(NULL, "bash", MKO, clean_exit(tab, 1)));
    }
    delimiter = findFirstDelimiter(argv, "\'\"");
    i = 0;
    int b;
    b = 0;
    while (argv[i] != '\0')
    {
        if (argv[i] == '\"')
            b++;
        i++;
    }
    if (b % 2 != 0)
    {
        delimiter = '\0';
        argv = removing_char(argv, '\\');
    }
    else 
    {
        b = 0;
        while (argv[b++] != '\0')
        {
            if (argv[b] == '\\' && argv[b + 1] == '\"')
                argv[b + 1] = '\'';
        }
    }
    b = 0;
    if (delimiter != '\0')
    {
        tab->cmd_args = ft_split(argv, delimiter);
        while (tab->cmd_args[1][b++] != '\0')
        {
            if (tab->cmd_args[1][b] == '\\' && tab->cmd_args[1][b + 1] == '\'')
            {
               tab->cmd_args[1][b + 1] = '\"';
            }
        }
        tab->cmd_args[1] = removing_char(tab->cmd_args[1], '\\');
        tab->cmd_args[0] = removing_char(tab->cmd_args[0], ' ');
    }
    else 
        tab->cmd_args = ft_split(argv, ' ');
    i = 0;
    if (tab->cmd_args[0][0] == '/' || tab->cmd_args[0][0] == '.' || ft_strrchr(tab->cmd_args[0], '/') != NULL)
    {
        tab->cmd = ft_strdup(tab->cmd_args[0]);
        if (access(tab->cmd, X_OK) != 0)
            exit(error_msg(PPX, tab->cmd_args[0], CNF, 126));
        return(0);
    }
    while (tab->paths[i])
    {
        tab->cmd_paths = ft_strjoin(tab->paths[i], "/");
        tab->cmd = ft_strjoin(tab->cmd_paths, tab->cmd_args[0]);
        if (access(tab->cmd, X_OK) == 0)
            return(0);
        free(tab->cmd);
        i++;
    }
    exit(error_msg(PPX, tab->cmd_args[0], CNF, 127));
}


int parsing_here_doc(t_pipex *tab)
{
    char *line;
    int pipe_fd[2];
    char *delimiter;
    int i;

    i = 0;
    line = NULL;
    delimiter = "EOF";

    if (pipe(pipe_fd) < 0)
        exit (error_msg(NULL, "bash", ECP, clean_exit(tab, 1)));
    while ((line = get_next_line(0)) != NULL)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
        {
            free(line);
            break;
        }
        i = 0;
        while (line[i++] != '\0')
            ft_putchar_fd(line[i], pipe_fd[1]);
        ft_putchar_fd('\n', pipe_fd[1]);
        free(line);
    }
    if (close(pipe_fd[1]))
        exit (error_msg(PPX, "open", CNC, clean_exit(tab, 1)));
    return (pipe_fd[0]);
}

char *removing_char(char *cmd, char delimiter)
{
    char *s1;
    char *s2;

    s1 = (char*)malloc(ft_strlen(cmd) + 1);
    if (!s1)
        return (NULL);
    s2 = s1;
    while(*cmd != '\0')
    {
        if (*cmd != delimiter)
            *s1++ = *cmd;
        cmd++; 
    }
    *s1 = '\0';
    return(s2);
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