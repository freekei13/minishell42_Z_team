/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:29:33 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/26 02:00:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"

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
	node->e_type = AST_ERROR;
	node->u_data.err.status_code = 2;
	node->u_data.err.err_message = message;
	return (node);
}

void	syntax_err_node(t_ast *node, int index)
{
	node->u_data.cmd.args[index] = NULL;
	free_all(node->u_data.cmd.args);
	free_redirects(node->u_data.cmd.redirects);
	err_ast(node, REDIR_UN);
}
