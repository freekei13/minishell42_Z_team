/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:57:57 by lalamino          #+#    #+#             */
/*   Updated: 2026/05/26 10:50:01 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "builtin.h"

char	***add_env(char ***env, char **add)
{
	int		i;
	int		j;
	char	**new_env;

	if (add == NULL)
		return (env);
	i = 0;
	while (add[i] && add[i] != NULL)
		i++;
	new_env = env_dup(env[0], i);
	j = 0;
	while (new_env[j])
		j++;
	i = -1;
	while (add[++i])
		new_env[j + i] = ft_strdup(add[i]);
	new_env[j + i] = NULL;
	env[0] = malloc(sizeof(char ***)* (i + j + 1));
	i = -1;
	while (new_env[++i])
		env[0][i] = ft_strdup(new_env[i]);
	env[0][i] = NULL;
	split_free(new_env);
	return (env);
}

char	**rmv_env2(char **env, char **rmv, int x, int i)
{
	int		j;
	int		r;
	char	**new_env;

	i = -1;
	j = -1;
	new_env = malloc(sizeof(char **) * (x + 1));
	while (env[++i])
	{
		r = -1;
		while (rmv[++r])
		{
			x = 0;
			while (env[i] && env[i][x] != '=')
				x++;
			if (env[i + 1] &&find_env(env, rmv[r]) == env[i] + x + 1)
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
	t_int	i;
	char	**new_env;

	if (rmv == NULL)
		return (env);
	i.i = 0;
	while (rmv[i.i] != NULL)
		i.i++;
	i.j = 0;
	while (env[i.j])
		i.j++;
	new_env = rmv_env2(env, rmv, i.j - i.i, 0);
	i.k = -1;
	while(new_env[++i.k])
		env[i.k] = ft_strdup(new_env[i.k]);
	env[i.k] = NULL;
	while (env[++i.k])
		free(env[i.k]);
	split_free(new_env);
	return (env);
}
