/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:22 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/08 14:39:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	export2(char ***env, char **valid_find, t_int i, char **cmd)
{
	char	**valid_add;
	char	**valid_chg;

	i.i = 0;
	while (valid_find[i.i])
		i.i++;
	valid_add = malloc(sizeof(char *) * (i.i + 1));
	valid_chg = malloc(sizeof(char *) * (i.i + 1));
	i.i = -1;
	i.j = -1;
	i.k = -1;
	while (valid_find[++i.i])
	{
		if (find_env(*env, valid_find[i.i]) != NULL)
			valid_chg[++i.j] = ft_strdup(cmd[i.i]);
		else if (find_env(*env, valid_find[i.i]) == NULL)
			valid_add[++i.k] = ft_strdup(cmd[i.i]);
	}
	valid_chg[++i.j] = NULL;
	valid_add[++i.k] = NULL;
	env = add_env(env, valid_add);
	*env = chg_env(*env, valid_chg);
	return ;
}

int	args_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	export(char ***env, char **cmd, t_exec *exc_data)
{
	char	**valid_find;
	t_int	i;

	exc_data->data->exit_status = 0;
	i.k = args_size(cmd);
	valid_find = malloc(sizeof(char *) * (i.k + 1));
	i.i = -1;
	i.j = -1;
	while (cmd[++i.i])
	{
		i.is = 0;
		if (cmd[i.i][0])
		{
			while (cmd[i.i][i.is]
					&& cmd[i.i][i.is] != '=')
				i.is++;
			if (cmd[i.i][i.is] == '=')
				valid_find[++i.j] = ft_substr(cmd[i.i], 0, i.is);
			else
				valid_find[++i.j] = ft_strdup(cmd[i.i]);
		}
	}
	valid_find[++i.j] = NULL;
	export2(env, valid_find, i, cmd);
	return ;
}
