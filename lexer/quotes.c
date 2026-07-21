/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:21:42 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/21 12:45:19 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_dquote	empty_str(t_dquote qt)
{
	char	*tempo;
	char	*réserve;
	
	while (qt.split[++qt.i])
	{
		tempo = ft_strdup(qt.split[qt.i]);
		réserve = ft_strdup(qt.temp);
		free(qt.temp);
		qt.temp = ft_strjoin(réserve, tempo);
		free(tempo);
		free(réserve);
		if (qt.split[qt.i][0] != '\0')
			break;
	}
	if (!qt.split[qt.i])
		--qt.i;
	return (qt);
}

char	*dqt_sentence(t_dquote qt)
{
	qt.i = -1;
	qt.save = NULL;
	qt.res = NULL;
	qt.temp = NULL;
	while (qt.split && qt.split[++qt.i])
	{
		qt.temp = ft_strdup(qt.split[qt.i]);
		if (qt.split[qt.i + 1] && qt.split[qt.i + 1][0] == '\0')
			qt = empty_str(qt);
		if (qt.res != NULL)
			free(qt.res);
		if ((qt.save && qt.save[0] != '\0') || (qt.temp && qt.temp[0] != '\0'))
			qt.res = ft_strjoin(qt.save, qt.temp);
		else
			qt.res = NULL;
		if (qt.save != NULL)
			free(qt.save);
		if (qt.temp != NULL)
			free(qt.temp);
		if (qt.res != NULL)
			qt.save = ft_strdup(qt.res);
	}
	if (qt.save != NULL)
	free(qt.save);
	return (qt.res);
}

void	split_free(char **split)
{
	int	i;

	i = -1;
	while (split[++i] && split[i] != NULL)
		free(split[i]);
	free(split);
}

char	*quote_sep(char *str, char **env, int ext_status)
{
	t_dquote	qt;

	qt.j = 0;
	qt.i = -1;
	qt.s = 0;
	if (quote_check(str) == -1 || !str)
		return (NULL);
	qt.quote = str[0];
	qt.split = malloc(sizeof (char *) * (ft_strlen(str) + 1));
	qt.split[qt.s] = NULL;
	if (str[0] != 34 && str[0] != 39 && str[0] != '$')
	{
		while (str[++qt.i] && str[qt.i] != 34 && str[qt.i] != 39
			&& str[qt.i] != '$')
			qt.quote = str[qt.i];
		qt.split[qt.s++] = ft_substr(str, qt.j, qt.i);
		qt.quote = str[qt.i];
		qt.j = qt.i;
	}
	qt.split[qt.s] = NULL;
	qt.split = dequote(qt, str, env, ext_status);
	// int k = 0;
	// while (qt.split[k])
	// {
    // 	printf("split[%d] = \"%s\"\n", k, qt.split[k]);
    // 	k++;
	// }
	qt.res = dqt_sentence(qt);
	//printf("res = \"%s\"\n", qt.res);
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
