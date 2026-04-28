/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:07 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/28 14:05:13 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	pwd_update(char **env, char *args)
{
	char	**pwd;

	pwd = malloc(sizeof(char **) * 3);
	pwd[0] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
	pwd[1] = ft_strjoin("PWD=", args);
	env = chg_env(env, pwd);
}

int		cd(char **args, char **env)
{
	t_int	i;

	i.i = -1;
	if (args_size(args) != 2)
		return ;
	if (args[1] == "-")
	{
		
	}
	else
	{
		i.ks = chdir(args[1]);
		if (i.ks == 1)
			pwd_update(env, args[1]);
		if (i.ks == 0)
		if (i.ks == -1)
	}
}
