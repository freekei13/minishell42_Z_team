/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:13:36 by csamakka          #+#    #+#             */
/*   Updated: 2026/06/17 01:58:35 by marvin           ###   ########.fr       */
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
		executer(ast->data.pipe.left, env, data.sigdata, 1);
	}
	else
	{
		dup2(data.pipefd[0], STDIN_FILENO);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		executer(ast->data.pipe.right, env, data.sigdata, 1);
	}
	free_ast(data.sigdata->root_ast);
	free_all(env);
	rl_clear_history();
	exit(0);
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
		waitpid(data->pid_left, &data->status, 0);
		waitpid(data->pid_right, &data->status, 0);
}
