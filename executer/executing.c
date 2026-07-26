/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:35:03 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/26 04:10:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

void	exc_data_init(t_exec *exc_data, t_data *data, int is_child)
{
	exc_data->fd_in = -1;
	exc_data->fd_out = -1;
	exc_data->is_child = is_child;
	exc_data->data = data;
}

int	ast_cmd_proces(t_ast *ast, char ***env, t_exec *exc_data)
{
	if (exc_data->is_child == 0 && heredoc_handle(ast, *exc_data) == -2)
		return (0);
	if (redirects(ast, exc_data) == -1 || !ast->u_data.cmd.args[0])
	{
		if (exc_data->fd_in != -1)
			close(exc_data->fd_in);
		if (exc_data->fd_out != -1)
			close(exc_data->fd_out);
		return (0);
	}
	if (builtin(ast, env, exc_data) == 1)
	{
		cmd_exec(ast, *env, exc_data);
		return (1);
	}
	else
	{
		if (exc_data->fd_in != -1)
			close(exc_data->fd_in);
		if (exc_data->fd_out != -1)
			close(exc_data->fd_out);
		return (1);
	}
}

void	executer(t_ast *ast, char ***env, t_data *data, int is_child)
{
	t_exec	exc_data;

	if (!ast)
		return ;
	exc_data_init(&exc_data, data, is_child);
	if (ast->e_type == AST_CMD)
	{
		if (ast_cmd_proces(ast, env, &exc_data) == 0)
			return ;
	}
	else if (ast->e_type == AST_PIPE)
	{
		if (is_child == 0 && heredoc_handle(ast, exc_data) == -2)
			return ;
		pipe_exec(ast, *env, &exc_data);
	}
	else if (ast->e_type == AST_ERROR)
		error_exit(ast->u_data.err.status_code,
			ft_strdup(ast->u_data.err.err_message), ast, &exc_data);
}
