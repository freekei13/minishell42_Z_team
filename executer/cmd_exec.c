/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:40:04 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/26 11:58:02 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"

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
	data.sigdata->pid = fork();
	if (data.sigdata->pid == -1)
		return (error_exit(1, NULL, ast, 1));
	if (data.sigdata->pid == 0)
	{
		signal_set(*data.sigdata);
		execve_cmd(ast, env, data);
	}
	sigint_after_cmd();
	if (data.fd_in != -1)
		close(data.fd_in);
	if (data.fd_out != -1)
		close(data.fd_out);
	waitpid(data.sigdata->pid, &data.status, 0);
	g_status = data.status >> 8;
	if ((data.status & 0x7f) == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}
