/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:32:43 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/31 00:32:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "parsing.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "signals.h"
# include <stdbool.h>

# define CMD_NF "command not found"
# define EOF_M "\nwarning: here-document delimited by end-of-file (wanted `"

typedef struct s_exec
{
	int			pipefd[2];
	int			fd_in;
	int			fd_out;
	pid_t		pid_left;
	pid_t		pid_right;
	int			status;
	int			is_child;
	t_data		*data;
}	t_exec;

void	executer(t_ast *ast, char ***env, t_data *data, int is_child);

char	*read_heredoc_line(void);
int		heredoc_handle(t_ast *ast, char **env, t_exec exc_data);
char	*hd_expand(char *line, char **env, int status);
char	*hd_join(char *a, char *b);
char	*hd_var(char *line, int *i, char **env, int status);
void	hd_term_setup(struct termios *term_save);

int		redirects(t_ast *ast, t_exec *exc_data);

void	pipe_exec(t_ast *ast, char **env, t_exec *exc_data);

char	*find_path(t_ast *ast, char **env);

char	**underscore_env(char **env, char *path);
void	cmd_exec(t_ast *ast, char **env, t_exec *exc_data);

void	error_exit(int status, char *message, t_ast *ast, t_exec *exc_data);
char	*err_message_custom(char *cause, char *message);
void	status_control(t_exec *exc_data);

#endif