/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:45:50 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/13 00:53:01 by vkhrabro         ###   ########.fr       */
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
    char *modified_args;
    /*char **splitted_args;*/
    char delimiter;


    i = 0;

    while (ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    tab->path_from_envp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
    tab->paths = ft_split(tab->path_from_envp, ':');
    modified_args = ft_strjoin(argv, " ");
    /*printf("The args string: %s\n", modified_args);*/
    delimiter = findFirstDelimiter(argv, "\'\"");
    /*printf("Delimiter found: %c\n", delimiter);*/
    if (delimiter != '\0')
    {
        tab->cmd_args = ft_split(argv, delimiter);
        tab->cmd_args[0] = removing_char(tab->cmd_args[0], ' ');
    }
    else 
        tab->cmd_args = ft_split(argv, ' ');
    /*i = 0;
    while (tab->cmd_args[i] != NULL)
    {
        printf("%s\n", tab->cmd_args[i]);
        i++;
    }
    return (1);*/

    i = 0;
    while (tab->paths[i])
    {
        tab->cmd_paths = ft_strjoin(tab->paths[i], "/");
        tab->cmd = ft_strjoin(tab->cmd_paths, tab->cmd_args[0]);
        /*printf("tab->cmd: %s\n", tab->cmd);
        printf("tab->cmd_args[0]: %s\n", tab->cmd_args[0]);*/
        if (access(tab->cmd, X_OK) == 0)
            return(0);
        free(tab->cmd);
        i++;
    }
    exit(EXIT_FAILURE);
}

int parsing_here_doc()
{
    char *line;
    int pipe_fd[2];
    char *delimiter;
    int i;

    i = 0;
    line = NULL;
    delimiter = "EOF";

    if (pipe(pipe_fd) == -1)
        exit(EXIT_FAILURE);
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
    close(pipe_fd[1]);
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

char **string_check(char **cmd, int num_strings)
{
    char *new_cmd;
    int i, j = 0;

    while (j < num_strings) 
    {
        new_cmd = NULL;
        i = 0;

        while (cmd[j][i] != '\0') {
            if (cmd[j][i] == 39 || cmd[j][i] == 34)
                break;
            i++;
        }

        if (cmd[j][i] != '\0') // Quotes found
        {
            if (ft_strchr(cmd[j], '\"') != NULL && ft_strchr(cmd[j], '\'') != NULL)
            {
                if (cmd[j][i] == '\"')
                {
                    new_cmd = removing_char(cmd[j], '\"');
                    free(cmd[j]);
                    cmd[j] = new_cmd;
                }
                else if (cmd[j][i] == '\'')
                {
                    new_cmd = removing_char(cmd[j], '\'');
                    free(cmd[j]);
                    cmd[j] = new_cmd;
                }
            }
            else if ((ft_strchr(cmd[j], '\"') != NULL) && (ft_strchr(cmd[j], '\'') == NULL))
            {
                new_cmd = removing_char(cmd[j], '\"');
                free(cmd[j]);
                cmd[j] = new_cmd;
            }
            else if ((ft_strchr(cmd[j], '\"') == NULL) && (ft_strchr(cmd[j], '\'') != NULL))
            {
                new_cmd = removing_char(cmd[j], '\'');
                free(cmd[j]);
                cmd[j] = new_cmd;
            }
        }
        j++;
    }
    return cmd;
}


