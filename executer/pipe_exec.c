/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:13:36 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/19 03:46:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	child_exec(t_ast *ast, char ***env, t_exec exc_data, int side)
{
	if (side == 0)
	{
		dup2(exc_data.pipefd[1], STDOUT_FILENO);
		close(exc_data.pipefd[0]);
		close(exc_data.pipefd[1]);
		executer(ast->data.pipe.left, env, exc_data.data, 1);
	}
	else
	{
		dup2(exc_data.pipefd[0], STDIN_FILENO);
		close(exc_data.pipefd[0]);
		close(exc_data.pipefd[1]);
		executer(ast->data.pipe.right, env, exc_data.data, 1);
	}
	free_ast(exc_data.data->root_ast);
	free_all(*env);
	rl_clear_history();
	exit(exc_data.data->exit_status);
}

void	pipe_exec(t_ast *ast, char ***env, t_exec *exc_data)
{
	if (pipe(exc_data->pipefd) == -1)
			return (error_exit(1, NULL, ast, exc_data));
		exc_data->pid_left = fork();
		if (exc_data->pid_left == -1)
			return (error_exit(1, NULL, ast, exc_data));
		if (exc_data->pid_left == 0)
			child_exec(ast, env, *exc_data, 0);
		exc_data->pid_right = fork();
		if (exc_data->pid_right == -1)
			return (error_exit(1, NULL, ast, exc_data));
		if (exc_data->pid_right == 0)
			child_exec(ast, env, *exc_data, 1);
		close(exc_data->pipefd[0]);
		close(exc_data->pipefd[1]);
		waitpid(exc_data->pid_left, &exc_data->status, 0);
		waitpid(exc_data->pid_right, &exc_data->status, 0);
		exc_data->data->exit_status = exc_data->status >> 8;
}
