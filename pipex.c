/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:54:59 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/25 18:38:52 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process(t_pipex *tab, int *end, char **argv, char *envp[])
{
	if ((dup2(tab->in_fd, STDIN_FILENO)) < 0)
		exit(clean_exit(tab, -1));
	if ((dup2(end[1], STDOUT_FILENO)) < 0)
		exit(clean_exit(tab, -1));
	close(end[0]);
	close(tab->in_fd);
	check_path(tab, argv[2], envp);
	if (execve(tab->cmd, tab->cmd_args, envp) == -1)
		exit(clean_exit(tab, 1));
	exit(EXIT_SUCCESS);
}

int	parent_process(t_pipex *tab, int *end, char **argv, char *envp[])
{
	if ((dup2(tab->out_fd, STDOUT_FILENO)) < 0)
		exit (error_msg(BSH, "2", BFD, clean_exit(tab, 1)));
	if ((dup2(end[0], STDIN_FILENO)) < 0)
		exit(clean_exit(tab, -1));
	close(end[1]);
	close(tab->out_fd);
	check_path(tab, argv[3], envp);
	if (execve(tab->cmd, tab->cmd_args, envp) == -1)
		exit(clean_exit(tab, 1));
	exit(EXIT_SUCCESS);
}

int	pipex(t_pipex *tab, char **args, char **envp)
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(tab, 1)));
	pid = fork();
	if (pid < 0)
		exit (error_msg(NULL, "bash", ECF, clean_exit(tab, 1)));
	else if (pid == 0)
		child_process(tab, end, args, envp);
	else
		parent_process(tab, end, args, envp);
	return (0);
}

int	ft_check_args(int argc, char **argv, t_pipex *tab)
{
	if (argc != 5)
		exit (error_msg(NULL, "bash", INA, 1));
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
		exit(clean_exit(tab, 1));
	initialize_tab(tab);
	ft_check_args(argc, argv, tab);
	pipex(tab, argv, envp);
	return (clean_exit(tab, 0));
}
