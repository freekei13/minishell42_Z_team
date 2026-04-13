/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:27 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 16:59:16 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"

void	cmd_node_loop(t_token *tokens, t_ast *node)
{
	int	i;
	
	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
		{
			node->data.cmd.args[i++] = ft_strdup(tokens->value);
			tokens = tokens->next;
		}
		else if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (!tokens->next)
			{
				err_ast(node, REDIRECTS_UN);
				return ;
			}
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

	if (!tokens)
		return (NULL);
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

t_token	*tokens_to_prev(t_token *tokens)
{
	while(tokens)
	{
		if (tokens->next == NULL || tokens->next->type == PIPE) 
			break ;
		tokens = tokens->next;	
	}
	return (tokens);
}

t_ast	*pipe_node_parser(t_token *tokens)
{
	t_token	*prev;
	t_ast	*node;
	t_token	*head;
	t_token	*pipe;
	
	head = tokens;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	if (tokens->type == PIPE)
		return (err_ast(node, PIPE_UNEXPECTED));
	node->type = AST_PIPE;
	tokens = tokens_to_prev(tokens);
	prev = tokens;
	pipe = prev->next;
	if (!tokens->next || !tokens->next->next)
		return (err_ast(node, PIPE_UNEXPECTED));
	else
		tokens = tokens->next->next;
	prev->next = NULL;
	node->data.pipe.left = parser(head);
	node->data.pipe.right = parser(tokens);
	prev->next = pipe;
	return (node);
}

t_ast	*parser(t_token *tokens)
{
	int			node_type;
	t_ast		*node;
	t_token		*head;
	
	if (!tokens)
		return (NULL);
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
