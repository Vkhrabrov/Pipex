/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:54:59 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/11 22:36:48 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_join(char **tab, const char *sep);
void free_tab(char **tab);

int child_process(t_pipex *tab, int *end, char **argv, char *envp[])
{
    if ((dup2(tab->in_fd, STDIN_FILENO)) < 0)
        return (-1);
    if ((dup2(end[1], STDOUT_FILENO)) < 0)
        return (-1);
    close(end[0]);
    close(tab->in_fd);
     if (ft_check_path(tab, argv[2], envp) == 1)
    {
        free(tab);
        exit(EXIT_FAILURE);
    }
    if (execve(tab->cmd, tab->cmd_args, envp) == -1)
    {
        perror("Execve error");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int parent_process(t_pipex *tab, int *end, char **argv, char *envp[])
{
    if ((dup2(tab->out_fd, STDOUT_FILENO)) < 0)
        return (-1);
    if ((dup2(end[0], STDIN_FILENO)) < 0)
        return (-1);
    close(end[1]);
    close(tab->out_fd);
     if (ft_check_path(tab, argv[3], envp) == 1)
    {
        free(tab);
        exit(EXIT_FAILURE);
    }
    if (execve(tab->cmd, tab->cmd_args, envp) == -1)
    {
        perror("Execve error");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int pipex(t_pipex *tab, char **args, char **envp)
{
    int end[2];
    pid_t pid;

    if (pipe(end) < 0)
    {
        perror("pipe");
        return (-1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
        child_process(tab, end, args, envp);
    else
        parent_process(tab, end, args, envp);
    return (0);
}

int ft_check_args(int argc, char **argv, t_pipex *tab)
{
    if (argc != 5)
    {
        perror("Not enough parameters for a program");
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0 || 
            ft_strncmp(argv[1], "<<", ft_strlen("<<")) == 0)
        tab->in_fd = parsing_here_doc();
    else
    {
        tab->in_fd = open(argv[1], O_RDONLY);
        if (tab->in_fd < 0)
        {                
            perror("Open error");
            exit(EXIT_FAILURE);
        }
    }
    tab->out_fd = open(argv[argc- 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
    if (tab->out_fd < 0)
    {
        perror("Open output error");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main(int argc, char **argv, char *envp[])
{
    t_pipex *tab;

    tab = (t_pipex *)malloc(sizeof(t_pipex));
	if (!tab)
		exit (EXIT_FAILURE);
    ft_initialize_tab(tab);
    if (ft_check_args(argc, argv, tab) == 1)
    {
        free(tab);
        exit(EXIT_FAILURE);
    }
    pipex(tab, argv, envp);
    free(tab);
    return (0);
}