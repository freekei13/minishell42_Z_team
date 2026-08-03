/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:57:57 by lalamino          #+#    #+#             */
/*   Updated: 2026/08/03 13:29:06 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "builtin.h"

char	**add_env(char **env, char **add)
{
	int		i;
	int		j;
	char	**new_env;

	if (add == NULL || add[0] == NULL)
		return (env);
	i = 0;
	while (add[i])
		i++;
	new_env = env_dup(env, i);
	j = 0;
	while (new_env[j])
		j++;
	i = -1;
	while (add[++i])
		new_env[j + i] = ft_strdup(add[i]);
	new_env[j + i] = NULL;
	split_free(env);
	env = new_env;
	return (env);
}

int	in_rmv(char *entry, char **rmv)
{
	int	i;
	int	j;

	i = -1;
	while (rmv[++i])
	{
		j = 0;
		while (rmv[i][j] && rmv[i][j] == entry[j])
			j++;
		if (rmv[i][j] == '\0' && entry[j] == '=')
			return (1);
	}
	return (0);
}

char	**rmv_env(char **env, char **rmv)
{
	char	**new_env;
	int		i;
	int		j;

	if (rmv == NULL || rmv[0] == NULL)
		return (env);
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (env);
	i = -1;
	j = -1;
	while (env[++i])
	{
		if (!in_rmv(env[i], rmv))
			new_env[++j] = ft_strdup(env[i]);
	}
	new_env[++j] = NULL;
	split_free(env);
	return (new_env);
}
