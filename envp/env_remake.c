/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:25:03 by lalamino          #+#    #+#             */
/*   Updated: 2026/05/12 13:22:20 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	env = make_env(new_env);
	split_free(new_env);
	return (env);
}

char	**chg_env2(char **env, char **change, char **fi_chg, char **new_env)
{
	t_int	i;

	i.i = -1;
	while (env[++i.i])
	{
		i.j = 0;
		i.js = 0;
		while(change[i.j][i.js] != '=')
			i.js++;
		while (change[i.j + 1] != NULL
				&& find_env(env, fi_chg[i.j]) != env[i.i] + i.js + 1)
		{
			i.j++;
			i.js = 0;
			while (change[i.j][i.js] && change[i.j][i.js] != '=')
				i.js++;
		}
		if (!change[i.j])
			new_env[i.i] = ft_strdup(env[i.i]);
		else
			new_env[i.i] = ft_strdup(change[i.j]);
	}
	new_env[i.i] = NULL;
	split_free(fi_chg);
	return (new_env);
}

char	**find_change(char **change)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	while (change[i])
		i++;
	res = malloc(sizeof(char **) * (i + 1));
	i = -1;
	while (change[++i] && change[i] != NULL)
	{
		j = 0;
		while (change[i][j] && change[i][j] != '=')
			j++;
		if (change[i][j] == '=')
			res[i] = ft_substr(change[i], 0, j);
	}
	res[i] = NULL;
	return (res);
}

char	**chg_env(char **env, char **change)
{
	int		i;
	char	**new_env;
	char	**find_chg;

	if (change == NULL)
		return (env);
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char **) * (i + 1));
	find_chg = find_change(change);
	new_env = chg_env2(env, change, find_chg, new_env);
	split_free(env);
	env = make_env(new_env);
	split_free(new_env);
	return (env);
}
