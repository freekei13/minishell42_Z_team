/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:22 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/16 14:42:22 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-in.h"

char	**export2(char **env, char **valid_find, t_int i, t_ast cmd)
{
	char	**new_env;
	char	**temp_env;
	char	**valid_add;
	char	**valid_chg;
	
	i.i = 0;
	while(valid_find[i.i])
		i.i++;
	valid_add = malloc(sizeof(char **) * (i.i + 1));
	valid_chg = malloc(sizeof(char **) * (i.i + 1));
	i.i = -1;
	i.j = -1;
	i.k = -1;
	while (valid_find[++i.i])
	{
		if (find_env(env, valid_find[i.i]) != NULL)
			valid_chg[++i.j] = ft_strdup(cmd.data.cmd.args[i.i]);
		else if (find_env(env, valid_find[i.i]) == NULL)
			valid_add[++i.k] = ft_strdup(cmd.data.cmd.args[i.i]);
	}
	temp_env = add_env(env, valid_add);
	new_env = chg_env(env, valid_chg);
	return(new_env);
}

char	**export(char **env, t_ast cmd)
{
	char	**valid_find;
	char	**new_env;
	t_int	i;

	i.k = 0;
	while(cmd.data.cmd.args[i.k])
		i.k++;
	valid_find = malloc(sizeof(char **)* (i.k + 1));
	i.i = -1;
	i.j = -1;
	while (cmd.data.cmd.args[++i.i])
	{
		i.is = 0;
		if (cmd.data.cmd.args[i.i][0])
		{
			while(cmd.data.cmd.args[i.i][i.is]
					&& cmd.data.cmd.args[i.i][i.is] != '=')
				i.is++;
			if (cmd.data.cmd.args[i.i][i.is] == '=')
				valid_find[++i.j] = ft_substr(cmd.data.cmd.args[i.i], 0, i.is);
			else
				valid_find[+i.j] = ft_strdup(cmd.data.cmd.args[i.i]);
		}
	}
	valid_find[++i.j] = NULL;
	new_env = export2(env, valid_find, i, cmd);
	return (new_env);
}
