/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:35:19 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 00:10:35 by csamakka         ###   ########.fr       */
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

void	error_exit(int status, char *message, t_ast *ast, int parent)
{
	if (message)
	{
		ft_putstr_fd(message, 2);
		free(message);
	}
	else
		perror("minishell");
	ast = NULL;
	if (parent == 0)
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

	tmp = ft_strjoin("minishell: ", cause);
	msg	= ft_strjoin(tmp, message);
	free(tmp);
	return (msg);
}
