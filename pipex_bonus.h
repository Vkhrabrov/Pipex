/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:29:59 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/25 18:48:41 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*to perror*/
# include <stdio.h>

/*boolean*/
# include <stdbool.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		here_doc;
	int		invalid_infile;
	int		i;
	int		b;
	char	delimiter;
	char	*d_hd;
	char	*path_from_envp;
	char	**paths;
	char	*cmd_paths;
	char	*path;
	char	**cmd_args;
	char	*cmd;
	int		cmd_count;
	int		argc_tab;
	int		heredoc;
	char	*line;
	char	**lines;
	int		num_lines;
	char	**temp;
}	t_pipex;

void	initialize_tab(t_pipex *tab);
int		parsing_here_doc(t_pipex *tab);
void	check_path(t_pipex *tab, char *argv, char *envp[]);
char	*get_next_line(int fd);
char	**string_check(char **cmd, int num_strings);
char	find_first_delimiter(const char *str, const char *delimiters);
char	*removing_char(char *cmd, char delimiter);
int		error_msg(char *first, char *second, char *thrd, int ret);
int		clean_exit(t_pipex *tab, int ret);
void	string_parsing_back_slashes(t_pipex *tab, char *argv);
void	string_parsing_quotes(t_pipex *tab, char *argv);
int		string_parsing_final(t_pipex *tab);
void	check_path_part_2(t_pipex *tab, char *argv);

# define BSH "bash: "
# define PPX "pipex: "
# define CNO ": Cannot open"
# define CNF ": command not found"
# define CNC ": Fd can not be closed"
# define PMD ": Permission denied"
# define BFD ": Bad file descriptor"
# define ECP ": error creating pipe"
# define ECF ": error creating fork"
# define NFD ": No such file or directory"
# define INA ": Invalid number of arguments"
# define MKO ": error trying to allocate memory"
# define DEFPATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

#endif