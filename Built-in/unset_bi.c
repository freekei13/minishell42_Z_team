/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:48 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/16 13:34:35 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-in.h"

char	**unset(char **env, t_ast cmd)
{
	char	**new_env;
	char	**valid_args;
	int		i;

	i = 0;
	while (cmd.data.cmd.args[i])
		i++;
	valid_args = malloc(sizeof(char **) * (i + 1));
	i = -1;
	while (cmd.data.cmd.args[++i] != NULL
			&& find_env(env, cmd.data.cmd.args[i]) != NULL)
		valid_args[i] = ft_strdup(cmd.data.cmd.args[i]);
	valid_args[i] = NULL;
	if (!cmd.data.cmd.args[i])
		new_env = rmv_env(env, valid_args);
	else
	{
		split_free(valid_args);
		printf("arguments non valides");
		return(env);
	}
	split_free(valid_args);
	return(new_env);
}
