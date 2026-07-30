/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:28:53 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/30 02:22:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token || value == NULL)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	free_tokens(t_token *lst)
{
	t_token	*current;
	t_token	*next;

	current = lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

// Field splitting POSIX : le resultat d'une expansion NON quotee est
// redecoupe sur les blancs. On n'applique le decoupage que si le mot source
// ne contient aucune quote — dans ce cas les seuls blancs presents dans le
// resultat viennent forcement d'une expansion, donc le decoupage est sur.
// Un mot sans blanc produit exactement un token : aucun changement.
void	add_word_tokens(t_token **tokens, char *raw, char *final)
{
	int		i;
	int		j;
	char	*field;

	if (ft_strchr(raw, 39) || ft_strchr(raw, 34))
	{
		add_token_back(tokens, new_token(final, WORD));
		return ;
	}
	i = 0;
	while (final[i])
	{
		while (is_blank(final[i]))
			i++;
		if (!final[i])
			break ;
		j = i;
		while (final[i] && !is_blank(final[i]))
			i++;
		field = ft_substr(final, j, i - j);
		add_token_back(tokens, new_token(field, WORD));
		free(field);
	}
}