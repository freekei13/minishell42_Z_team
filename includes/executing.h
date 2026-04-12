/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:32:43 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/12 14:36:25 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parsing.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_exec
{
	int		pipefd[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid_left;
	pid_t	pid_right;
}	t_exec;

void	executer(t_ast *ast, char **env);

void	here_doc(t_ast *ast, t_exec *data);
void	redirects(t_ast *ast, t_exec *data);

void	pipe_exec(t_ast *ast, char **env, t_exec *data);

char	*find_path(t_ast *ast, char **env);

void	cmd_exec(t_ast *ast, char **env, t_exec data);

void	error_exit(int status, char *message, t_ast *ast, int parent);
char	*err_message_custom(char *cause, char *message);
void	free_ast(t_ast *ast);

#endif