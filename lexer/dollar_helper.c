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

// pousser le str jusqu'avant le $, puis 
// avancer qt.i jusqu'à la fin du nom de variable (en gérant le cas expand
// pour un $ qui suit immédiatement).
t_dquote	dollar_scan(t_dquote qt, char *str)
{
	if (qt.j + 1 != qt.i && qt.i != 0 && str[qt.j] != '$')
		qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	qt.j = qt.i;
	while (str[qt.i] && str[qt.i] != 34 && str[qt.i] != ' '
		&& str[qt.i] != '\'' && (str[qt.i] != '$' || qt.expand == 0))
	{
		if (str[qt.i] == '$')
			qt.expand = 1;
		qt.i++;
	}
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
		qt.split[qt.s++] = ft_strdup("$");
	else
		qt.split[qt.s++] = ft_strdup("");
	free(substr_tmp);
	return (qt);
}
