/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:35:03 by csamakka          #+#    #+#             */
/*   Updated: 2026/06/16 18:20:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"


int	heredoc_handle(t_ast *ast)
{
	int				pipefd[2];
	t_redirect		*redirects_tmp;
	int				ret;

	if (!ast)
		return (0);
	if (ast->type == AST_PIPE)
	{
		ret = heredoc_handle(ast->data.pipe.left);
		if (ret == -2)
			return (-2);
		ret = heredoc_handle(ast->data.pipe.right);
		if (ret == -2)
			return (-2);
	}
	else if (ast->type == AST_CMD)
	{
		redirects_tmp = ast->data.cmd.redirects;
		while (redirects_tmp)
		{
			if (redirects_tmp->type == HEREDOC)
			{
				if (pipe(pipefd) == -1)
					return (0);
				ret = here_doc_loop(redirects_tmp, pipefd);
				close(pipefd[1]);
				if (ret == -2)
					return (-2);
				if (ret == -1)
				{
					ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2);
    				ft_putstr_fd(redirects_tmp->file, 2);
    				ft_putstr_fd("')\n", 2);
					redirects_tmp->fd = pipefd[0];
    				return (-1);
				}
				redirects_tmp->fd = pipefd[0];
			}
			redirects_tmp = redirects_tmp->next;
		}
	}
	return (0);
}

void	executer(t_ast *ast, char **env, t_sigdata *sigdata, int is_child)
{
	t_exec	data;

	if (!ast)
		return ;
	data.fd_in = -1;
	data.fd_out = -1;
	data.sigdata = sigdata;
	if (ast->type == AST_CMD)
	{
		if (is_child == 0 && heredoc_handle(ast) == -2)
			return ;
		if (redirects(ast, &data) == -1 || !ast->data.cmd.args[0])
		{
			if (data.fd_in != -1)
				close(data.fd_in);
			if (data.fd_out != -1)
				close(data.fd_out);
			return ;
		}
		if (builtin(ast, &env) == 1)
			cmd_exec(ast, env, data);
	}
	else if (ast->type == AST_PIPE)
	{
		if (is_child == 0 && heredoc_handle(ast) == -2)
			return ;
		pipe_exec(ast, env, &data);
	}
	else if (ast->type == AST_ERROR)
		error_exit(ast->data.err.status_code, 
			ft_strdup(ast->data.err.err_message), ast, 1);
}
