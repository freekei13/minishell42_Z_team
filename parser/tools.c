/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:29:33 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/03 15:41:22 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"

void	print_ast(t_ast *ast)
{
	int			i;
	char		*redir;
	t_redirect	*head;
	
	i = 0;
	head = ast->data.cmd.redirects;
	if (ast->type == AST_CMD)
	{
		printf("CMD :\n");
		if (ast->data.cmd.redirects)
		{
			while (ast->data.cmd.redirects)
			{
				if(ast->data.cmd.redirects->type == HEREDOC
					|| ast->data.cmd.redirects->type == REDIRECT_IN)
				{
					if (ast->data.cmd.redirects->type == HEREDOC)
						redir = "<<";
					else if (ast->data.cmd.redirects->type == REDIRECT_IN)
						redir = "<";
					printf("%s %s ", redir, ast->data.cmd.redirects->file);
				}
				ast->data.cmd.redirects = ast->data.cmd.redirects->next;
			}
			printf("---> ");
		}
		while (ast->data.cmd.args[i])
		{
			printf("%s ", ast->data.cmd.args[i]);
			i++;
		}
		ast->data.cmd.redirects = head;
		if (ast->data.cmd.redirects)
		{
			if (ast->data.cmd.args[0])
				printf("---> ");
			while (ast->data.cmd.redirects)
			{
				if(ast->data.cmd.redirects->type == APPEND
					|| ast->data.cmd.redirects->type == REDIRECT_OUT)
				{
					if (ast->data.cmd.redirects->type == APPEND)
						redir = ">>";
					else if (ast->data.cmd.redirects->type == REDIRECT_OUT)
						redir = ">";
					printf("%s %s ", redir, ast->data.cmd.redirects->file);
				}
				ast->data.cmd.redirects = ast->data.cmd.redirects->next;
			}
		}
		printf("\n");
	}
	else if (ast->type == AST_PIPE)
	{
		printf("PIPE:\n");
	}
}