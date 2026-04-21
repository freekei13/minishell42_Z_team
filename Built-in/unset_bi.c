/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:48 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/21 12:01:31 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-in.h"

char	**mlc_init(char **cmd)
{
	char	**mlc;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	mlc = malloc(sizeof(char **) * (i + 1));
	return (mlc);
}

char	**unset(char **env, t_ast cmd)
{
	char	**new_env;
	char	**valid_args;
	int		i;
	int		s;

	i = 0;
	valid_args = mlc_init(cmd.data.cmd.args);
	i = -1;
	s = -1;
	while (cmd.data.cmd.args[++i] != NULL)
	{
		if (find_env(env, cmd.data.cmd.args[i]) != NULL)
			valid_args[++s] = ft_strdup(cmd.data.cmd.args[i]);
	}
	valid_args[++s] = NULL;
	if (s >= 0)
		new_env = rmv_env(env, valid_args);
	else
	{
		split_free(valid_args);
		printf("arguments non valides\n");
		return (env);
	}
	split_free(valid_args);
	return (new_env);
}
