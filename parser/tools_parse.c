/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:29:33 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 16:56:04 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"

void	print_ast(t_ast *ast, int level)
{
	int			i;
	char		*type;
	t_redirect	*head;
	t_redirect	*tmp;
	
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
	tmp = ast->data.cmd.redirects;
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
		if (tmp)
		{
			while (tmp)
			{
				if(tmp->type == HEREDOC
					|| tmp->type == REDIRECT_IN)
				{
					if (tmp->type == HEREDOC)
						type = "<<";
					else if (tmp->type == REDIRECT_IN)
						type = "<";
					printf("%s %s ", type, tmp->file);
				}
				tmp = tmp->next;
			}
			printf("---> ");
		}
		i = 0;
		while (ast->data.cmd.args[i])
		{
			printf("%s ", ast->data.cmd.args[i]);
			i++;
		}
		tmp = head;
		if (tmp)
		{
			if (ast->data.cmd.args[0])
				printf("---> ");
			while (tmp)
			{
				if(tmp->type == APPEND
					|| tmp->type == REDIRECT_OUT)
				{
					if (tmp->type == APPEND)
						type = ">>";
					else if (tmp->type == REDIRECT_OUT)
						type = ">";
					printf("%s %s ", type, tmp->file);
				}
				tmp = tmp->next;
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
	else if (ast->type == AST_ERROR)
	{
		printf("ERROR(%d)\n", ast->data.err.status_code);
	}
}

int	lst_word_counter(t_token *tokens)
{
	int		word_nb;
	t_token	*tmp;

	word_nb = 0;
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			word_nb++;
		tmp = tmp->next;
	}
	return (word_nb);
}

void	*err_ast(t_ast *node, char *message)
{
	node->type = AST_ERROR;
	node->data.err.status_code = 2;
	node->data.err.err_message = message;
	return (node);
}
