/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:35:03 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/19 03:36:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

int	heredoc_ast_cmd(t_redirect *redirects, int *pipefd, t_exec exc_data)
{
	int	ret;
	
	while (redirects)
	{
		if (redirects->type == HEREDOC)
		{
			if (pipe(pipefd) == -1)
				return (0);
			ret = here_doc_loop(redirects, pipefd, exc_data);
			close(pipefd[1]);
			if (ret == -2)
				return (-2);
			if (ret == -1)
			{
				ft_putstr_fd("\nwarning: here-document delimited by end-of-file (wanted `", 2);
    			ft_putstr_fd(redirects->file, 2);
    			ft_putstr_fd("')\n", 2);
				redirects->fd = pipefd[0];
    			return (-1);
			}
			redirects->fd = pipefd[0];
		}
		redirects = redirects->next;
	}
	return (0);
}

int	heredoc_handle(t_ast *ast, t_exec exc_data)
{
	int				pipefd[2];
	t_redirect		*redirects_tmp;
	int				ret;

	if (!ast)
		return (0);
	if (ast->type == AST_PIPE)
	{
		ret = heredoc_handle(ast->data.pipe.left, exc_data);
		if (ret == -2)
			return (-2);
		ret = heredoc_handle(ast->data.pipe.right, exc_data);
		if (ret == -2)
			return (-2);
	}
	else if (ast->type == AST_CMD)
	{
		redirects_tmp = ast->data.cmd.redirects;
		ret = heredoc_ast_cmd(redirects_tmp, pipefd, exc_data);
		return (ret);
	}
	return (0);
}

void	exc_data_init(t_exec *exc_data, t_data *data, int is_child)
{
	exc_data->fd_in = -1;
	exc_data->fd_out = -1;
	exc_data->is_child = is_child;
	exc_data->data = data;
}

void	executer(t_ast *ast, char ***env, t_data *data, int is_child)
{
	t_exec	exc_data;

	if (!ast)
		return ;
	exc_data_init(&exc_data, data, is_child);
	if (ast->type == AST_CMD)
	{
		if (is_child == 0 && heredoc_handle(ast, exc_data) == -2)
			return ;
		if (redirects(ast, &exc_data) == -1 || !ast->data.cmd.args[0])
		{
			if (exc_data.fd_in != -1)
				close(exc_data.fd_in);
			if (exc_data.fd_out != -1)
				close(exc_data.fd_out);
			return ;
		}
		if (builtin(ast, env, &exc_data) == 1)
			cmd_exec(ast, *env, &exc_data);
	}
	else if (ast->type == AST_PIPE)
	{
		if (is_child == 0 && heredoc_handle(ast, exc_data) == -2)
			return ;
		pipe_exec(ast, env, &exc_data);
	}
	else if (ast->type == AST_ERROR)
		error_exit(ast->data.err.status_code, 
			ft_strdup(ast->data.err.err_message), ast, &exc_data);

}
