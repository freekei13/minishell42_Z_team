/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:35:19 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/10 23:03:16 by csamakka         ###   ########.fr       */
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

void	error_exit(int status, char *message, t_ast *ast)
{
	if (message)
		ft_putstr_fd(message, 2);
	else
		perror("minishell: ");
	free_ast(ast);
	exit (status);
}