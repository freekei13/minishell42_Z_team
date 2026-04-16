/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:24:55 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/16 13:26:54 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	**env_dup(char **env, int x)
{
	char **new_env;
	int	i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char **) * (i + 1 + x));
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	return (new_env);
}

char	**make_env(char **env)
{
	int		i;
	char	**res;
	int		j;

	j = 0;
	while (env[j])
		j++;
	i = -1;
	res = malloc(sizeof(char **) * (j + 1));
	while (env[++i])
		res[i] = ft_strdup(env[i]);
	res[i] = NULL;
	return (res);
}

char	*find_env(char **env, char *cherche)
{
	int	i;
	int	j;

	j = -1;
	if (cherche == NULL)
		return (NULL);
	while (env[++j] != NULL)
	{
		i = 0;
		if (cherche[0] == env[j][0])
		{
			while (cherche[i] == env[j][i])
				i++;
		}
		if (env[j][i] == '=')
			return (env[j] + i + 1);
	}
	return (NULL);
}

