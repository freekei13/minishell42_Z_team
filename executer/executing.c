/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:35:03 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/26 11:59:51 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

void	executer(t_ast *ast, char **env, t_sigdata *sigdata);

int	heredoc_handle(t_ast *ast)
{
	int			pipefd[2];
	t_redirect	*redirects_tmp;

	if (!ast)
		return (0);
	if (ast->type == AST_PIPE)
	{
		heredoc_handle(ast->data.pipe.left);
		heredoc_handle(ast->data.pipe.right);
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
				here_doc_loop(redirects_tmp, pipefd);
				close(pipefd[1]);
				redirects_tmp->fd = pipefd[0];
			}
			redirects_tmp = redirects_tmp->next;
		}
	}
	return (0);
}

void	executer(t_ast *ast, char **env, t_sigdata *sigdata)
{
	t_exec	data;
	
	if (!ast)
		return ;
	data.fd_in = -1;
	data.fd_out = -1;
	data.sigdata = sigdata;
	if (ast->type == AST_CMD)
	{
		heredoc_handle(ast);
		if (redirects(ast, &data) == -1 || !ast->data.cmd.args[0])
		{
			if (data.fd_in != -1)
				close(data.fd_in);
			if (data.fd_out != -1)
				close(data.fd_out);
			return ;
		}
		if (builtin(ast, &env) == 1)
		{
			heredoc_handle(ast);
			cmd_exec(ast, env, data);
		}
	}
	else if (ast->type == AST_PIPE)
		pipe_exec(ast, env, &data);
	else if (ast->type == AST_ERROR)
		error_exit(ast->data.err.status_code, 
			ft_strdup(ast->data.err.err_message), ast, 1);
}
