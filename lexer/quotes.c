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

// char	*quote_sep(char *str)
// {
// 	t_dquote qt;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	if (quote_check(str) == -1 || !str)
// 		return (NULL);
// 	qt.quote = str[0];
// 	qt.temp1 = NULL;
// 	if (str[0] != 34 && str[0] != 39)
// 	{
// 		while (str[++i] && str[i] != 34 && str[i] != 39)
// 			qt.temp1 = ft_substr(str, j, i);
// 		qt.quote = str[i];
// 	}
// 	qt.temp2 = NULL;
// 	qt.res = NULL;
// 	while(str[++i])
// 	{
// 		if (str[i] == qt.quote)
// 			j = i;
// 		else
// 		{
// 			while (str[i] != qt.quote && str[i])
// 				i++;
// 			qt.temp2 = ft_substr(str, j+1, i-j-1);
// 		}
// 		if (qt.temp2 != NULL)
// 		{
// 			qt.res = NULL;
// 			qt.res = ft_strjoin(qt.temp1, qt.temp2);
// 			if(qt.temp1 != NULL)
// 				free(qt.temp1);
// 			free(qt.temp2);
// 			qt.temp1 = NULL;
// 			qt.temp2 = NULL;
// 			if (str[i + 1] && qt.res != NULL)
// 			{
// 				qt.temp1 = ft_strdup(qt.res);
// 				free(qt.res);
// 			}
// 		}
// 	}
// 	printf("d-quoted : %s\n", qt.res);
// 	if (qt.res == NULL)
// 		return (qt.temp1);
// 	return (qt.res);
// }

char	*quote_sep(char *str)
{
	t_dquote	qt;
	int			i;
	int			j;
	int			s;

	j = 0;
	i = -1;
	s = 0;
	qt.quote = str[0];
	qt.split = malloc(sizeof (char **) * ft_strlen(str));
	if (quote_check(str) == -1 || !str)
		return (NULL);
	if (str[0] != 34 && str[0] != 39)
	{
		while (str[++i] && str[i] != 34 && str[i] != 39)
			qt.quote = str[i];
		qt.split[s++] = ft_substr(str, j, i);
		qt.quote = str[i];
		j = i;
	}
	qt.q_val = 1; 
	while(str[++i])
	{
		if (str[i] == qt.quote && i != 0)
		{
			qt.split[s++] = ft_substr(str, j + 1, i - j - 1);
			qt.q_val = 0;
			if (str[i + 1] && (str[i + 1] == 34 || str[i + 1] == 39))
			{
				qt.quote = str[++i];
				qt.q_val = 1;
			}
			j = i;
			// while(str[++i] && (str[i] == 34 || str[i] == 39) && qt.q_val == 0)
			// {
			// 	qt.quote = str[i];
			// 	qt.q_val = 1;
			// 	if (str[i + 1] == qt.quote)
			// 		qt.q_val = 0;
			// }
			// if (str[i] && str[i] == qt.quote)
			// {
			// 	if (j+1 != i)
			// 		qt.split[s++] = ft_substr(str, j + 1, i - j - 1);
			// 	j = i;
			// 	qt.q_val = 0;
			// }
		}
		else if (str[i] == '$' && qt.quote == 34)
		{
			if (j+1 != i)
				qt.split[s++] = ft_substr(str, j + 1, i - j - 1);
			j = i;
			while (str[i] && str[i] != 34 && str[i] != 32 && str[i] != 39)
				i++;
			qt.split[s++] = ft_substr(str, j, i - j);
			if (str[i] == qt.quote && str[i + 1] == 39)
			{
				qt.quote = str[++i];
				qt.q_val = 1;
			}
			else if (str[i] == qt.quote && str[i + 1] != qt.quote)
				qt.q_val = 0;
			j = i;
			if (str[i - 1] == 39 || str[i] == 32 || (str[i] == 39 && str[i-1] != 34))
				j--;
			if (str[i] == qt.quote)
				i++;
		}
		else if (str[i] && qt.q_val == 0)
		{
			while (str[i] && str[i] != 39 && str[i] != 34)
				i++;
			qt.split[s++] = ft_substr(str, j + 1, i - j - 1);
			if (str[i] && (str[i] == 39 || str[i] == 34))
			{
				qt.q_val = 1;
				qt.quote = str[i];
				i++;
			}
			j = i - 1;
		}
	}
	qt.split[s] = NULL;
	i = -1;
	qt.save = NULL;
	qt.res = NULL;
	qt.temp = NULL;
	while (qt.split[++i])
	{
		qt.temp = ft_strdup(qt.split[i]);
		if (qt.res != NULL)
			free(qt.res);
		qt.res = ft_strjoin(qt.save, qt.temp);
		if (qt.save != NULL)
			free(qt.save);
		if (qt.temp != NULL)
			free(qt.temp);
		qt.save = ft_strdup(qt.res);
		printf("split %i : %s\n", i, qt.split[i]);
	}
	free(qt.save);
	printf("no coma : %s\n", qt.res);
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
			while(str[i] && str[i] != c)
				i++;
		}
		if (!str[i])
			return (-1);
	}
	return (0);
}
