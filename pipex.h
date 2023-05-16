/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:33:43 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/16 23:45:07 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

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
#include <stdbool.h>


typedef struct s_pipex
{
    int in_fd;
    int out_fd;
    int here_doc;
    int invalid_infile;
    char    *path_from_envp;
    char    **paths;
    char    *cmd_paths;
    char    **cmd_args;
    char    *cmd;
    int     cmd_count;
} t_pipex;

void        ft_initialize_tab(t_pipex *tab);
int         parsing_here_doc();
int         ft_check_path(t_pipex *tab, char *argv, char *envp[]);
char	    *get_next_line(int fd);
char        **string_check(char **cmd, int num_strings);
char        findFirstDelimiter(const char *str, const char *delimiters);
char        *removing_char(char *cmd, char delimiter);
int         error_msg(char *first, char *second, char *thrd, int ret);
int	        clean_exit(t_pipex *tab, int ret);

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