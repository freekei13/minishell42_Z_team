/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:35:19 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/04 00:36:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == AST_CMD)
	{
		free_all(ast->data.cmd.args);
		free_redirects(ast->data.cmd.redirects);
	}
	else if (ast->type == AST_PIPE)
	{
		free_ast(ast->data.pipe.left);
		free_ast(ast->data.pipe.right);
	}
	free(ast);
}

void	error_exit(int status, char *message, t_ast *ast, t_exec *exc_data)
{
	exc_data->data->exit_status = status;
	
	if (message)
	{
		ft_putstr_fd(message, 2);
		free(message);
	}
	else
		perror("minishell");
	if (exc_data->data->pid == 0)
	{
		free_ast(ast);
		exit (status);
	}
	return ;
}

char	*err_message_custom(char *cause, char *message)
{
	char	*msg;
	char	*tmp;
	char	*new_str;
	
	new_str = ft_strjoin(cause, ": ");
	tmp = ft_strjoin("minishell: ", new_str);
	free(new_str);
	new_str = ft_strjoin(tmp, message);
	free(tmp);
	msg = ft_strjoin(new_str, "\n");
	free(new_str);
	return (msg);
}
