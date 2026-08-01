/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:28:53 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/01 02:04:24 by marvin           ###   ########.fr       */
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
	token->quoted = 0;
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

// Le mot delimiteur porte l'unique interrupteur qui decide du sort de TOUT le
// corps du heredoc : delimiteur non quote -> les $ sont expanses, delimiteur
// quote -> le corps est recopie tel quel. Une seule quote suffit, ou qu'elle
// soit dans le mot : << 'EOF', << "EOF" et << lim'' sont tous "quotes".
void	mark_hd_delim(t_token *lst, char *raw)
{
	if (!lst)
		return ;
	while (lst->next)
		lst = lst->next;
	if (ft_strchr(raw, 39) || ft_strchr(raw, 34))
		lst->quoted = 1;
}
