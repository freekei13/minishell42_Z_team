/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:29:33 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/30 03:18:29 by marvin           ###   ########.fr       */
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

// Un noeud AST_ERROR quelque part dans l'arbre doit faire abandonner TOUTE
// la ligne, comme bash : rien ne s'execute, meme les commandes valides des
// autres cotes du pipe. Parcours gauche d'abord pour signaler l'erreur la
// plus a gauche, comme bash le fait.
t_ast	*ast_find_error(t_ast *ast)
{
	t_ast	*found;

	if (!ast)
		return (NULL);
	if (ast->e_type == AST_ERROR)
		return (ast);
	if (ast->e_type != AST_PIPE)
		return (NULL);
	found = ast_find_error(ast->u_data.pipe.left);
	if (found)
		return (found);
	return (ast_find_error(ast->u_data.pipe.right));
}