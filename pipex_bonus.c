/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:32:47 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/25 18:52:05 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_pipex *tab, int *end, char **argv, char *envp[])
{
	close(end[0]);
	if (dup2(tab->in_fd, STDIN_FILENO) < 0)
		exit(clean_exit(tab, 1));
	if (dup2(end[1], STDOUT_FILENO) < 0)
		exit(clean_exit(tab, 1));
	close(tab->in_fd);
	close(end[1]);
	check_path(tab, argv[tab->b], envp);
	if (execve(tab->cmd, tab->cmd_args, envp) == -1)
		exit(clean_exit(tab, 1));
}

int	pipex_extension(t_pipex *tab, char **args, char **envp)
{
	if (dup2(tab->in_fd, STDIN_FILENO) < 0)
		exit(clean_exit(tab, -1));
	if (dup2(tab->out_fd, STDOUT_FILENO) < 0)
		exit(clean_exit(tab, 1));
	check_path(tab, args[tab->b], envp);
	if (execve(tab->cmd, tab->cmd_args, envp) == -1)
		exit(clean_exit(tab, 1));
	return (0);
}

int	pipex(t_pipex *tab, int argc, char **args, char **envp)
{
	int		end[2];
	pid_t	pid;

	if (tab->heredoc == 1)
		tab->b = 3;
	else
		tab->b = 2;
	while (tab->b < argc - 2)
	{
		if (pipe(end) < 0)
			exit(clean_exit(tab, 1));
		pid = fork();
		if (pid < 0)
			exit(clean_exit(tab, 1));
		else if (pid == 0)
			child_process(tab, end, args, envp);
		close(tab->in_fd);
		tab->in_fd = end[0];
		close(end[1]);
		tab->b++;
	}
	pipex_extension(tab, args, envp);
	return (0);
}

int	ft_check_args(int argc, char **argv, t_pipex *tab)
{
	if (argc < 5)
		exit (error_msg(NULL, "bash", INA, 1));
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		tab->d_hd = ft_strdup(argv[2]);
		if (tab->d_hd[0] != '\0')
			tab->d_hd = ft_strjoin(tab->d_hd, "\n");
		if (tab->d_hd)
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
		exit(clean_exit(tab, 1));
	initialize_tab(tab);
	ft_check_args(argc, argv, tab);
	pipex(tab, argc, argv, envp);
	return (clean_exit(tab, 0));
}
