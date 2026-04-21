/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remake_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:57:57 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/21 12:02:04 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	**add_env(char **env, char **add)
{
	int		i;
	int		j;
	char	**new_env;

	if (add == NULL)
		return (env);
	i = 0;
	while (add[i] != NULL)
		i++;
	new_env = env_dup(env, i);
	j = 0;
	while (new_env[j])
		j++;
	i = -1;
	while (add[++i])
		new_env[j + i] = ft_strdup(add[i]);
	new_env[j + i] = NULL;
	return (new_env);
}
