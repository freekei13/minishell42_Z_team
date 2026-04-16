/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:25:03 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/15 14:44:56 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	**rmv_env2(char **env, char **rmv, int x, int i)
{
	int		j;
	int		r;
	char	**new_env;

	i = -1;
	j = -1;
	new_env = malloc(sizeof(char **) * x);
	while (env[++i])
	{
		r = -1;
		while (rmv[++r])
		{
			x = 0;
			while (env[i][x] != '=')
				x++;
			if (find_env(env, rmv[r]) == env[i] + x + 1)
			{
				i++;
				r = -1;
			}
		}
		new_env[++j] = ft_strdup(env[i]);
	}
	new_env[++j] = NULL;
	return (new_env);
}

char	**rmv_env(char **env, char **rmv)
{
	int		i;
	int		j;
	char	**new_env;

	if (rmv == NULL)
		return (env);
	i = 0;
	while (rmv[i] != NULL)
		i++;
	j = 0;
	while (env[j])
		j++;
	new_env = rmv_env2(env, rmv, j + i - i, 0);
	split_free(env);
	return (new_env);
}

char	**chg_env2(char **env, char **change, char **new_env)
{
	int	i;
	int	j;
	int	c;
	char *chg;

	chg = NULL;
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (change[j] != NULL && find_env(env, chg) != env[i] + c + 1)
		{
			c = 0;
			while (change[j][c] && change[j][c] != '=')
				c++;
			chg = ft_substr(change[j], 0, c);
			j++;
		}
		if (!change[j])
			new_env[i] = ft_strdup(env[i]);
		else
			new_env[i] = ft_strdup(change[j]);
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**chg_env(char **env, char **change)
{
	int		i;
	char	**new_env;

	if (change == NULL)
		return (env);
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char **) * (i + 1));
	i = -1;
	chg_env2(env, change, new_env);
	split_free(env);
	return (new_env);
}
