/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:40:10 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/31 00:48:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"

t_redirect	*new_redirect(char *value, int type, int quoted)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->file = ft_strdup(value);
	redirect->type = type;
	redirect->expand = 1;
	if (quoted)
		redirect->expand = 0;
	redirect->next = NULL;
	return (redirect);
}

void	add_redirect_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*current;

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

void	free_redirects(t_redirect *lst)
{
	t_redirect	*current;
	t_redirect	*next;

	current = lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
}
