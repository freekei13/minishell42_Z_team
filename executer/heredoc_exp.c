/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:08:26 by marvin            #+#    #+#             */
/*   Updated: 2026/07/31 00:08:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	*hd_join(char *a, char *b)
{
	char	*res;

	if (!a || !b)
		return (free(a), free(b), NULL);
	res = ft_strjoin(a, b);
	free(a);
	free(b);
	return (res);
}

// Valeur d'un $ dans un corps de heredoc. Memes regles de nom que
// dollar_scan() : $? -> code de retour, un chiffre -> parametre positionnel
// vide, sinon [A-Za-z_][A-Za-z0-9_]*. Un $ isole reste litteral.
char	*hd_var(char *line, int *i, char **env, int status)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
	if (line[*i] == '?')
		return ((*i)++, ft_itoa(status));
	if (ft_isdigit(line[*i]))
		return ((*i)++, ft_strdup(""));
	start = *i;
	while (line[*i] == '_' || ft_isalnum(line[*i]))
		(*i)++;
	if (start == *i)
		return (ft_strdup("$"));
	name = ft_substr(line, start, *i - start);
	val = find_env(env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

// Dans un corps de heredoc les quotes sont INERTES : pas de decoupage en mots,
// pas de suppression de quotes, meme les apostrophes ne protegent de rien.
// Seuls les $ sont interpretes, et ils le sont partout. D'ou la sortie de bash
// pour un delimiteur non quote : "$USER" -> "csamakka" et '$USER' -> 'csamakka'
// (guillemets et apostrophes recopies tels quels, $ expanse entre les deux).
// C'est pour cette raison que quote_sep() est inutilisable ici : elle ferait
// disparaitre les quotes. Libere la ligne d'origine.
char	*hd_expand(char *line, char **env, int status)
{
	char	*res;
	int		i;
	int		j;

	res = ft_strdup("");
	i = 0;
	while (res && line[i])
	{
		j = i;
		while (line[i] && line[i] != '$')
			i++;
		res = hd_join(res, ft_substr(line, j, i - j));
		if (res && line[i] == '$')
			res = hd_join(res, hd_var(line, &i, env, status));
	}
	free(line);
	if (!res)
		return (ft_strdup(""));
	return (res);
}

// Isole la mise en place du terminal pour garder here_doc_loop sous 25 lignes.
// Renvoie l'ancien etat via le pointeur plutot qu'en valeur : un prototype
// "struct termios ..." casserait l'alignement du bloc dans executing.h.
void	hd_term_setup(struct termios *term_save)
{
	struct termios	term_new;

	sigint_heredoc();
	tcgetattr(STDIN_FILENO, term_save);
	term_new = *term_save;
	term_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_new);
}
