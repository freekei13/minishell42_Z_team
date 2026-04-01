/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:27 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/02 01:26:34 by csamakka         ###   ########.fr       */
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

void	cmd_node_loop(t_token *tokens, t_ast *node)
{
	int	i;
	
	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
		{
			node->data.cmd.args[i++] = tokens->value;
			tokens = tokens->next;
		}
		else if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			add_redirect_back(&node->data.cmd.redirects,
				new_redirect(tokens->next->value, tokens->type));
			tokens = tokens->next->next;
		}
	}
	node->data.cmd.args[i] = NULL;
}

t_ast	*cmd_node_parser(t_token *tokens)
{
	t_ast		*node;
	int			type_word_nb;

	type_word_nb = lst_word_counter(tokens);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = AST_CMD;
	node->data.cmd.args = malloc(sizeof(char *) * (type_word_nb + 1));
	node->data.cmd.redirects = NULL;
	cmd_node_loop(tokens, node);
	return (node);
}

t_ast	*parser(t_token *tokens);

t_ast	*pipe_node_parser(t_token *tokens)
{
	t_token		*prev;
	t_ast		*node;
	t_token		*head;
	
	head = tokens;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = AST_PIPE;
	while(tokens)
	{
		if ( tokens->next == NULL || tokens->next->type == PIPE) 
			break ;
		tokens = tokens->next;	
	}
	prev = tokens;
	if (!tokens->next || !tokens->next->next)
		tokens = NULL;
	else
		tokens = tokens->next->next;
	prev->next = NULL;
	node->data.pipe.left = parser(head);
	node->data.pipe.right = parser(tokens);
	return (node);
}

t_ast	*parser(t_token *tokens)
{
	int			node_type;
	t_ast		*node;
	t_token		*head;
	
	node_type = 0;
	head = tokens;
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
		node = cmd_node_parser(tokens);
	else
		node = pipe_node_parser(tokens);
	return (node);
}
