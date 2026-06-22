/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:40:04 by csamakka          #+#    #+#             */
/*   Updated: 2026/06/22 23:22:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"

void	execve_cmd(t_ast *ast, char **env, t_exec exc_data)
{
	char	*path;

	if (exc_data.fd_in != -1)
		dup2(exc_data.fd_in, STDIN_FILENO);
	if (exc_data.fd_out != -1)
		dup2(exc_data.fd_out, STDOUT_FILENO);
	if (exc_data.fd_in != -1)
		close(exc_data.fd_in);
	if (exc_data.fd_out != -1)
		close(exc_data.fd_out);
	// builtin(ast->data.cmd.args, env);
	if (!ast->data.cmd.args[0] || ast->data.cmd.args[0][0] == '\0')
		error_exit(127, err_message_custom("''",
				": command not found\n"), ast, 0);
	path = find_path(ast, env);
	if (!path)
		error_exit(127, err_message_custom(ast->data.cmd.args[0],
				": command not found\n"), ast, 0);
	execve(path, ast->data.cmd.args, env);
	free(path);
	error_exit(126, NULL, ast, 0);
}

void	cmd_exec(t_ast *ast, char **env, t_exec data)
{
	exc_data.data->pid = fork();
	if (exc_data.data->pid == -1)
		return (error_exit(1, NULL, ast, 1));
	if (exc_data.data->pid == 0)
	{
		signal_set(*exc_data.data);
		execve_cmd(ast, env, exc_data);
	}
	sigint_after_cmd();
	if (exc_data.fd_in != -1)
		close(exc_data.fd_in);
	if (exc_data.fd_out != -1)
		close(exc_data.fd_out);
	waitpid(exc_data.data->pid, &exc_data.status, 0);
	exc_data.data->exit_status = exc_data.status >> 8;
	if ((data.status & 0x7f) == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}
