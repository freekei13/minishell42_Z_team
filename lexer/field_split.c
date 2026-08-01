/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 01:26:54 by marvin            #+#    #+#             */
/*   Updated: 2026/08/01 01:26:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

// Marque d'un \1 les blancs issus d'une expansion NON quotee (q_val == 0),
// pour qu'add_word_tokens sache ou couper. Un blanc venu d'une partie quotee
// n'est jamais marque, donc jamais coupe : c'est toute la difference entre
// "$X" et $X. Le marqueur ne survit pas au decoupage.
char	*mark_split(char *s, int q_val)
{
	int	i;

	if (!s || q_val != 0)
		return (s);
	i = -1;
	while (s[++i])
	{
		if (is_blank(s[i]))
			s[i] = 1;
	}
	return (s);
}

// Field splitting POSIX : le mot final peut melanger des parties quotees et
// le resultat d'expansions non quotees. On ne coupe que sur les marqueurs
// poses par mark_split, jamais sur un blanc litteral. Exemple :
// X="  A  B  " puis "1"$X'2' -> quatre mots : 1, A, B, 2.
void	add_word_tokens(t_token **tokens, char *final)
{
	int		i;
	int		j;
	char	*field;

	if (!ft_strchr(final, 1))
	{
		add_token_back(tokens, new_token(final, WORD));
		return ;
	}
	i = 0;
	while (final[i])
	{
		while (final[i] == 1)
			i++;
		if (!final[i])
			break ;
		j = i;
		while (final[i] && final[i] != 1)
			i++;
		field = ft_substr(final, j, i - j);
		add_token_back(tokens, new_token(field, WORD));
		free(field);
	}
}
