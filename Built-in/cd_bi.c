/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:07 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/29 12:12:24 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int	cdERR(char **args)
// {
	
// }

void	pwd_update(char **env, char *path)
{
	char	**pwd;

	pwd = malloc(sizeof(char **) * 3);
	pwd[0] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
	pwd[1] = ft_strjoin("PWD=", path);
	pwd[2] = NULL;
	env = chg_env(env, pwd);
	split_free(pwd);
}

int		cd(char **args, char **env)
{
	t_int	i;

	i.i = -1;
	if (args_size(args) != 2)
		return (0);
	if (args[1] && strncmp(args[1], "-", 2) == 0)
	{
		i.ks = chdir(find_env(env, "OLDPWD"));
		if (i.ks == 0)
			pwd_update(env, find_env(env, "OLDPWD"));
		else if (i.ks == 1)
			return (0);
	}
	else
	{
		i.ks = chdir(args[1]);
		if (i.ks == 0)
			pwd_update(env, args[1]);
		else if (i.ks == -1)
			return (0);
	}
	return (1);
}
