/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:40:04 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 00:46:20 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	execve_cmd(t_ast *ast, char **env, t_exec data)
{
	char	*path;
	
	if (data.fd_in != -1)
		dup2(data.fd_in, STDIN_FILENO);
	if (data.fd_out != -1)
		dup2(data.fd_out, STDOUT_FILENO);
	if (data.fd_in != -1)
		close(data.fd_in);
	if (data.fd_out != -1)
		close(data.fd_out);
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
	pid_t	pid_cmd;

	pid_cmd = fork();
	if (pid_cmd == -1)
		return (error_exit(1, NULL, ast, 1));
	if (pid_cmd == 0)
		execve_cmd(ast, env, data);
	if (data.fd_in != -1)
		close(data.fd_in);
	if (data.fd_out != -1)
		close(data.fd_out);
	waitpid(pid_cmd, NULL, 0);
}
