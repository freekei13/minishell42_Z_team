/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 00:26:25 by marvin            #+#    #+#             */
/*   Updated: 2026/07/25 00:26:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

// Blancs reconnus par le tokenizer, identiques a ceux de bash (espace et
// tabulation). Les autres caracteres de controle (\v, \f, \r) sont des
// caracteres ordinaires pour bash et ne separent pas les mots.
int	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// Delimiteur de heredoc : POSIX impose une simple suppression des quotes,
// SANS expansion ("cat << $USER" attend une ligne "$USER" litterale, et
// "$US"E"R" donne le delimiteur $USER apres suppression des quotes).
char	*heredoc_delim(char *word)
{
	char	*res;
	int		i;
	int		j;
	char	q;

	res = malloc(ft_strlen(word) + 1);
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	q = 0;
	while (word[++i])
	{
		if (q == 0 && (word[i] == 34 || word[i] == 39))
			q = word[i];
		else if (q == word[i])
			q = 0;
		else
			res[j++] = word[i];
	}
	res[j] = '\0';
	return (res);
}

// pousser le str jusqu'avant le $, puis 
// avancer qt.i jusqu'à la fin du nom de variable (en gérant le cas expand
// pour un $ qui suit immédiatement).
t_dquote	dollar_scan(t_dquote qt, char *str)
{
	if (qt.j + 1 != qt.i && qt.i != 0)
		qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	qt.j = qt.i;
	qt.i++;
	if (str[qt.i] == '?' || ft_isdigit(str[qt.i]))
		qt.i++;
	else
		while (str[qt.i] == '_' || ft_isalnum(str[qt.i]))
			qt.i++;
	// while (str[qt.i] && str[qt.i] != 34 && !is_blank(str[qt.i])
	// 	&& str[qt.i] != '\'' && (str[qt.i] != '$' || qt.expand == 0))
	// {
	// 	if (str[qt.i] == '$')
	// 		qt.expand = 1;
	// 	qt.i++;
	// }
	return (qt);
}

//Responsabilité : extraire le nom, chercher dans env,
//décider entre valeur trouvée / $? / $ littéral (nom vide) / chaîne vide,
//et pousser le résultat.
t_dquote	dollar_resolve(t_dquote qt, char *str, char **env, int ext_status)
{
	char	*substr_tmp;
	char	*find_env_tmp;

	substr_tmp = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	find_env_tmp = find_env(env, substr_tmp);
	if (find_env_tmp != NULL)
		qt.split[qt.s++] = ft_strdup(find_env_tmp);
	else if (str[qt.j] == '$' && str[qt.j + 1] == '?')
	{
		qt.i = qt.j + 1;
		qt.split[qt.s++] = ft_itoa(ext_status);
	}
	else if (substr_tmp[0] == '\0')
	{
		if((str[qt.i] == '\"' || str[qt.i] == '\'') && qt.q_val == 0)
			qt.split[qt.s++] = ft_strdup("");
		else
			qt.split[qt.s++] = ft_strdup("$");
	}
	else
		qt.split[qt.s++] = ft_strdup("");
	free(substr_tmp);
	return (qt);
}
