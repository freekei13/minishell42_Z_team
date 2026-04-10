/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:21:42 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/08 12:52:59 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*dqt_sentence(t_dquote qt)
{
	qt.i = -1;
	qt.save = NULL;
	qt.res = NULL;
	qt.temp = NULL;
	while (qt.split[++qt.i])
	{
		qt.temp = ft_strdup(qt.split[qt.i]);
		if (qt.res != NULL)
			free(qt.res);
		qt.res = ft_strjoin(qt.save, qt.temp);
		if (qt.save != NULL)
			free(qt.save);
		if (qt.temp != NULL)
			free(qt.temp);
		qt.save = ft_strdup(qt.res);
	}
	free(qt.save);
	qt.i = -1;
	return (qt.res);
}

void	split_free(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

char	*quote_sep(char *str, char **env)
{
	t_dquote	qt;

	qt.j = 0;
	qt.i = -1;
	qt.s = 0;
	qt.quote = str[0];
	qt.split = malloc(sizeof (char **) * ft_strlen(str));
	qt.split[qt.s] = NULL;
	if (quote_check(str) == -1 || !str)
		return (NULL);
	if (str[0] != 34 && str[0] != 39 && str[0] != '$')
	{
		while (str[++qt.i] && str[qt.i] != 34 && str[qt.i] != 39
			&& str[qt.i] != '$')
			qt.quote = str[qt.i];
		qt.split[qt.s++] = ft_substr(str, qt.j, qt.i);
		qt.quote = str[qt.i];
		qt.j = qt.i;
	}
	qt.split = dequote(qt, str, env);
	qt.res = dqt_sentence(qt);
	printf("no coma : %s\n", qt.res);
	split_free(qt.split);
	return (qt.res);
}

int	quote_check(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
		}
		if (!str[i])
			return (-1);
	}
	return (0);
}
