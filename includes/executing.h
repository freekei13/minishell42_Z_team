/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:32:43 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/22 22:02:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parsing.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "signals.h"
# include <stdbool.h>

extern int g_signal;

# define CMD_NF "command not found"

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

int		here_doc_loop(t_redirect *redirects, int *pipefd, t_exec exc_data);
int		redirects(t_ast *ast, t_exec *exc_data);

void	pipe_exec(t_ast *ast, char ***env, t_exec *exc_data);

char	*find_path(t_ast *ast, char **env);

void	cmd_exec(t_ast *ast, char **env, t_exec *exc_data);

void	error_exit(int status, char *message, t_ast *ast, t_exec *exc_data);
char	*err_message_custom(char *cause, char *message);
void	free_ast(t_ast *ast);
void	status_control(t_exec *exc_data);

#endif