/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:29:33 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/03 20:22:14 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"

void	print_ast(t_ast *ast, int level)
{
	int			i;
	char		*type;
	t_redirect	*head;
	
	i = 0;
	if (!ast)
	{
		printf("level %d -- ", level);
		while (i < level)
		{
			printf("        ");
			i++;
		}
		printf("NULL\n");
		return ;
	}
	i = 0;
	head = ast->data.cmd.redirects;
	if (ast->type == AST_CMD)
	{
		printf("level %d -- ", level);
		while (i < level)
		{
			printf("        ");
			i++;
		}
		type = "CMD";
		printf("%s : ", type);
		i = 0;
		if (ast->data.cmd.redirects)
		{
			while (ast->data.cmd.redirects)
			{
				if(ast->data.cmd.redirects->type == HEREDOC
					|| ast->data.cmd.redirects->type == REDIRECT_IN)
				{
					if (ast->data.cmd.redirects->type == HEREDOC)
						type = "<<";
					else if (ast->data.cmd.redirects->type == REDIRECT_IN)
						type = "<";
					printf("%s %s ", type, ast->data.cmd.redirects->file);
				}
				ast->data.cmd.redirects = ast->data.cmd.redirects->next;
			}
			printf("---> ");
		}
		i = 0;
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
						type = ">>";
					else if (ast->data.cmd.redirects->type == REDIRECT_OUT)
						type = ">";
					printf("%s %s ", type, ast->data.cmd.redirects->file);
				}
				ast->data.cmd.redirects = ast->data.cmd.redirects->next;
			}
		}
		printf("\n");
	}
	else if (ast->type == AST_PIPE)
	{
		printf("level %d -- ", level);
		while (i < level)
		{
			printf("        ");
			i++;
		}
		type = "PIPE";
		printf("%s\n", type);
		print_ast(ast->data.pipe.left, level + 1);
		print_ast(ast->data.pipe.right, level + 1);
	}
}
