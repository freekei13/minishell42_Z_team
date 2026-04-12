/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:13:36 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 00:05:28 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	child_exec(t_ast *ast, char **env, t_exec data, int side)
{
	if (side == 0)
	{
		dup2(data.pipefd[1], STDOUT_FILENO);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		executer(ast->data.pipe.left, env);
		exit(0);
	}
	else
	{
		dup2(data.pipefd[0], STDIN_FILENO);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		executer(ast->data.pipe.right, env);
		exit(0);
	}
}

void	pipe_exec(t_ast *ast, char **env, t_exec *data)
{
	if (pipe(data->pipefd) == -1)
			return (error_exit(1, NULL, ast, 1));
		data->pid_left = fork();
		if (data->pid_left == -1)
			return (error_exit(1, NULL, ast, 1));
		if (data->pid_left == 0)
			child_exec(ast, env, *data, 0);
		data->pid_right = fork();
		if (data->pid_right == -1)
			return (error_exit(1, NULL, ast, 1));
		if (data->pid_right == 0)
			child_exec(ast, env, *data, 1);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		waitpid(data->pid_left, NULL, 0);
		waitpid(data->pid_right, NULL, 0);
}
