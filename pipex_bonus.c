/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:32:47 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/24 01:01:53 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void child_process(t_pipex *tab, int *end, char **argv, char *envp[], int i)
{
    close(end[0]);  // Closing the read end as we won't read anything in child process.
    if (dup2(tab->in_fd, STDIN_FILENO) < 0)   // Replace the standard input with the input file.
        exit(EXIT_FAILURE);
    if (dup2(end[1], STDOUT_FILENO) < 0)  // Replace the standard output with the write end of the pipe.
        exit(EXIT_FAILURE);

    close(tab->in_fd);  // No longer need this after dup2
    close(end[1]);  // No longer need this after dup2

    check_path(tab, argv[i], envp);

    if (execve(tab->cmd, tab->cmd_args, envp) == -1)
    {
        perror("Execve error");
        exit(EXIT_FAILURE);
    }
}

/*int	parent_process(t_pipex *tab, int *end, char **argv, char *envp[])
{
	if ((dup2(tab->out_fd, STDOUT_FILENO)) < 0)
		exit (error_msg(BSH, "2", BFD, clean_exit(tab, 1)));
	if ((dup2(end[0], STDIN_FILENO)) < 0)
		return (-1);
	close(end[1]);
	close(tab->out_fd);
	check_path(tab, argv[3], envp);
	if (execve(tab->cmd, tab->cmd_args, envp) == -1)
	{
		perror("Execve error");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}*/

int pipex(t_pipex *tab, int argc, char **args, char **envp)
{
    int     end[2];
    pid_t   pid;
    int     i;

    if (tab->heredoc == 1)
        i = 3;
    else
        i = 2;

    while (i < argc - 2)
    {
        if (pipe(end) < 0)  // Create a pipe.
            exit(EXIT_FAILURE);

        pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);
        else if (pid == 0)  // In child process, execute the command and write to the pipe.
            child_process(tab, end, args, envp, i);

        close(tab->in_fd);  // Close the previous in_fd
        tab->in_fd = end[0];  // Update the in_fd to the read end of the pipe.
        close(end[1]);  // Close the write end of the pipe.

        /*wait(NULL);  // Wait for the child process to finish.*/

        i++;
    }

    // For the last command, replace the standard input with the read end of the last pipe and the standard output with the output file.
    if (dup2(tab->in_fd, STDIN_FILENO) < 0)
        return (-1);
    if (dup2(tab->out_fd, STDOUT_FILENO) < 0)
        exit(EXIT_FAILURE);

    check_path(tab, args[i], envp);

    if (execve(tab->cmd, tab->cmd_args, envp) == -1)
    {
        perror("Execve error");
        exit(EXIT_FAILURE);
    }

    return (0);
}

int	ft_check_args(int argc, char **argv, t_pipex *tab)
{
	if (argc < 5)
		exit (error_msg(NULL, "bash", INA, 1));
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0
		|| ft_strncmp(argv[1], "<<", ft_strlen("<<")) == 0)
    {
        tab->delimiter_heredoc = ft_strdup(argv[2]);
        if (tab->delimiter_heredoc[0] != '\0')
            tab->delimiter_heredoc = ft_strjoin(tab->delimiter_heredoc, "\n");
        if (tab->delimiter_heredoc)
        {
            tab->heredoc = 1;
		    tab->in_fd = parsing_here_doc(tab);
        }
    }
	else
		tab->in_fd = open(argv[1], O_RDONLY);
	if (tab->in_fd < 0)
		error_msg(PPX, argv[1], NFD, 1);
	tab->out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (tab->out_fd < 0)
		exit(error_msg(PPX, argv[4], CNO, 1));
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	*tab;

	tab = (t_pipex *)malloc(sizeof(t_pipex));
	if (!tab)
		exit (EXIT_FAILURE);
	initialize_tab(tab);
	ft_check_args(argc, argv, tab);
	pipex(tab, argc, argv, envp);
	return (clean_exit(tab, 0));
}