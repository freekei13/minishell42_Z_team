/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:40:04 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/22 23:46:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"

void	path_checker(char *path, t_ast *ast, t_exec *exc_data)
{
	struct	stat	st;	

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) == true)
		{
			free(path);
			error_exit(126, err_message_custom(ast->data.cmd.args[0],
					"Is a directory"), ast, exc_data);
		}
	}
	else
	{
		free(path);
		error_exit(127, NULL, ast, exc_data);
	}
}

void	execve_cmd(t_ast *ast, char **env, t_exec *exc_data)
{
	char			*path;

	if (exc_data->fd_in != -1)
		dup2(exc_data->fd_in, STDIN_FILENO);
	if (exc_data->fd_out != -1)
		dup2(exc_data->fd_out, STDOUT_FILENO);
	if (exc_data->fd_in != -1)
		close(exc_data->fd_in);
	if (exc_data->fd_out != -1)
		close(exc_data->fd_out);
	if (!ast->data.cmd.args[0] || ast->data.cmd.args[0][0] == '\0')
		error_exit(127, err_message_custom("''", CMD_NF), ast, exc_data);
	if (ft_strchr(ast->data.cmd.args[0], '/') != NULL)
	{
		path = ft_strdup(ast->data.cmd.args[0]);
		path_checker(path, ast, exc_data);
	}
	else
		path = find_path(ast, env);
	if (!path)
		error_exit(127, err_message_custom(ast->data.cmd.args[0],
				CMD_NF), ast, exc_data);
	execve(path, ast->data.cmd.args, env);
	free(path);
	error_exit(126, NULL, ast, exc_data);
}

void	cmd_exec(t_ast *ast, char **env, t_exec *exc_data)
{
	exc_data->data->pid = fork();
	if (exc_data->data->pid == -1)
		return (error_exit(1, NULL, ast, exc_data));
	if (exc_data->data->pid == 0)
	{
		signal_set(*exc_data->data);
		execve_cmd(ast, env, exc_data);
	}
	if (exc_data->fd_in != -1)
		close(exc_data->fd_in);
	if (exc_data->fd_out != -1)
		close(exc_data->fd_out);
	if (!exc_data->is_child)
		sigint_after_cmd();
	else
		sigint_silent_child();
	waitpid(exc_data->data->pid, &exc_data->status, 0);
	status_control(exc_data);
}
