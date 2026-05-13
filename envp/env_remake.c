/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:25:03 by lalamino          #+#    #+#             */
/*   Updated: 2026/05/13 11:46:01 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	i = -1;
	while (env[++i])
		env[i] = ft_strdup(new_env[i]);
	env[i] = NULL;
	split_free(new_env);
	return (env);
}
