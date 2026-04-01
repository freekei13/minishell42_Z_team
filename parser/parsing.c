/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:27 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/01 22:18:34 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"
#include "lexing.h"

// Algorithme du parser
// - cherche token pipe. si trouve cree un noeud pipe.
// 	- gauche et droite
// - si pas de pipe.
// 	- cree un noeud cmd

t_ast	*parser(t_token *tokens)
{
	t_token		*head;
	int			node_type;
	t_ast		*node;
	t_ast		**node_cmd;
	int			type_word_nb;
	int			i;

	head = tokens;
	node_type = 0;
	type_word_nb = 0;
	i = 0;
	while(tokens)
	{
		if (tokens->type == PIPE)
		{
			node_type = 1;
			break ;
		}
		tokens = tokens->next;	
	}
	tokens = head;
	if (node_type == 0)
	{
		while(tokens && tokens->type != PIPE)
		{
			if (tokens->type == WORD)
				type_word_nb++;
			tokens = tokens->next;
		}
		node = malloc(sizeof(t_ast));
		node->type = AST_CMD;
		node->data.cmd.args = malloc(sizeof(char *) * (type_word_nb + 1));
		tokens = head;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == WORD)
			{
				node->data.cmd.args[i] = tokens->value;
				i++;
				tokens = tokens->next;
			}
			else if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT
				|| tokens->type == APPEND || tokens->type == HEREDOC)
			{
				add_redirect_back(node->data.cmd.redirects,
					new_redirect(tokens->next->value, tokens->type));
				tokens = tokens->next->next;
			}
		}
		node->data.cmd.args[i] = NULL;
	}
	else
	{
		node->type = AST_PIPE;
	}
	return (node);
}