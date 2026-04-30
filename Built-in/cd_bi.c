/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:07 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/30 11:56:28 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int	cdERR(char **args)
// {
	
// }

char	**pwd_update(char **env, char *path)
{
	char	**pwd;

	pwd = malloc(sizeof(char **) * 3);
	pwd[0] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
	pwd[1] = ft_strjoin("PWD=", ft_strjoin(find_env(env, "PWD"),
		ft_strjoin("/", path)));
	pwd[2] = NULL;
	env = chg_env(env, pwd);
	split_free(pwd);
	return (env);
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
			env = pwd_update(env, find_env(env, "OLDPWD"));
		else if (i.ks == -1)
			return (0);
	}
	else
	{
		i.ks = chdir(args[1]);
		if (i.ks == 0)
			env = pwd_update(env, args[1]);
		else if (i.ks == -1)
			return (0);
	}
	return (1);
}
//glr a changer l env