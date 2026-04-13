/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:35:03 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 16:24:28 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	executer(t_ast *ast, char **env)
{
	t_exec	data;
	
	if (!ast)
		return ;
	data.fd_in = -1;
	data.fd_out = -1;
	if (ast->type == AST_CMD)
	{
		if (redirects(ast, &data) == -1)
			return ;
		cmd_exec(ast, env, data);
	}
	else if (ast->type == AST_PIPE)
		pipe_exec(ast, env, &data);
	else if (ast->type == AST_ERROR)
		error_exit(ast->data.err.status_code, 
			ft_strdup(ast->data.err.err_message), ast, 1);
}
