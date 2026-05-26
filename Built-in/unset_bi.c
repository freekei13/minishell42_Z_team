/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:48 by lalamino          #+#    #+#             */
/*   Updated: 2026/05/20 13:36:38 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

void	unset(char ***env, char **cmd)
{
	char	**valid_args;
	int		i;
	int		s;

	i = 0;
	valid_args = mlc_init(cmd);
	i = -1;
	s = -1;
	while (cmd[++i] != NULL)
	{
		if (find_env(*env, cmd[i]) != NULL)
			valid_args[++s] = ft_strdup(cmd[i]);
	}
	valid_args[++s] = NULL;
	if (s > 0)
		*env = rmv_env(*env, valid_args);
	else
	{
		split_free(valid_args);
		printf("unset - arguments non valides\n");
		return ;
	}
	split_free(valid_args);
	return ;
}
