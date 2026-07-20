/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:59:33 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/20 14:04:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_dquote	spaces(t_dquote qt, char *str)
{
	while (str[qt.i] && str[qt.i] != 39 && str[qt.i] != 34)
		qt.i++;
	qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	if (str[qt.i] && (str[qt.i] == 39 || str[qt.i] == 34))
	{
		qt.q_val = 1;
		qt.quote = str[qt.i];
		qt.i++;
	}
	qt.j = qt.i;
	return (qt);
}

t_dquote	parenthese(t_dquote qt, char *str)
{
	qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	qt.q_val = 0;
	if (str[qt.i + 1] && (str[qt.i + 1] == 34 || str[qt.i + 1] == 39))
	{
		if ((str[qt.i] == 34 && str[qt.i + 1] == 34) ||
				(str[qt.i] == 39 &&str[qt.i + 1] == 39))
		{
			qt.i +=2;
			qt.j = qt.i;
			while (str[qt.i] && str[qt.i] != 34 && str[qt.i] != 39 &&
					str[qt.i] != 36)
				qt.i++;
			qt.split[qt.s++] = ft_substr(str, qt.j, qt.i - qt.j);
		}
		qt.quote = str[++qt.i];
		qt.q_val = 1;
	}
	qt.j = qt.i;
	return (qt);
}

t_dquote	dollar(t_dquote qt, char *str, char **env, int ext_status)
{
	if (qt.j + 1 != qt.i && qt.i != 0 && str[qt.j] != 36)
	{
		qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	}
	qt.j = qt.i;
	while (str[qt.i] && str[qt.i] != 34 && str[qt.i] != 32 && str[qt.i] != 39 &&
				(str[qt.i] != 36 || qt.$ == 0))
	{
		if (str[qt.i] == 36)
			qt.$ = 1;
		qt.i++;
	}
	if (find_env(env, ft_substr(str, qt.j + 1, qt.i - qt.j - 1)) != NULL)
		qt.split[qt.s++] = ft_strdup(find_env(env, ft_substr(str, qt.j + 1,
						qt.i - qt.j - 1)));
	else if (str[qt.j + 1] == '?')
	{
		qt.i = qt.j += 1;
		qt.split[qt.s++] = ft_itoa(ext_status);
	}
	else if (!str[qt.j + 1] || str[qt.j + 1] == '\0')
		qt.split[qt.s++] = ft_strdup("$");
	else if (find_env(env, ft_substr(str, qt.j + 1, qt.i - qt.j - 1)) == NULL)
		qt.split[qt.s++] = ft_strdup("");
	if (str[qt.i] == qt.quote && str[qt.i + 1] == 39)
	{
		qt.quote = str[++qt.i];
		qt.q_val = 1;
	}
	else if (str[qt.i] == qt.quote && str[qt.i + 1] != qt.quote)
		qt.q_val = 0;
	qt.j = qt.i;
	if (str[qt.i - 1] == 39 || str[qt.i] == 32 || (str[qt.i] == 39
			&& str[qt.i - 1] != 34))
		qt.j--;
	if (str[qt.i] && str[qt.i] == qt.quote && str[qt.i] != 36)
			qt.i++;
	else if (str[qt.i] && str[qt.i] == 36)
		--qt.i;
	//printf("split : %s", qt.split[qt.s - 1]);
	qt.$ = 0;
	return (qt);
}

char	**dequote(t_dquote qt, char *str, char **env, int ext_status)
{
	if (qt.i != -1)
	{
		qt.i -= 1;
		qt.j -= 1;
	}
	if (qt.i != -1 && str[qt.i] == '\0')
		return (qt.split);
	qt.q_val = 1;
	if (str[qt.i + 1] == '$')
		qt.q_val = 0;
	qt.$ = 0;
	while (str[++qt.i])
	{
		if (str[qt.i] == qt.quote && qt.i != 0 && qt.quote != '$')
			qt = parenthese(qt, str);
		else if (str[qt.i] == '$' && (qt.quote == 34 || qt.q_val == 0))
			qt = dollar(qt, str, env, ext_status);
		else if ((str[qt.i] && qt.q_val == 0))
			qt = spaces(qt, str);
		if (str[qt.i] == '\0')
			break ;
	}
	qt.split[qt.s] = NULL;
	return (qt.split);
}
