/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:07 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/30 03:52:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_update(char **env)
{
	char	*pwd[3];
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (find_env(env, "PWD"))
		pwd[1] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
	else
		pwd[1] = ft_strdup("OLDPWD=");
	pwd[0] = ft_strjoin("PWD=", cwd);
	pwd[2] = NULL;
	chg_env(env, pwd);
	free(cwd);
	free(pwd[0]);
	free(pwd[1]);
}

void	cd_error(char *arg, char *msg, t_exec *exc_data)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
	{
		exc_data->data->exit_status = 1;
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	else
		exc_data->data->exit_status = 2;
	ft_putendl_fd(msg, 2);
}

char	*cd_target(char **args, char **env, t_exec *exc_data)
{
	char	*dest;

	if (!args[1])
	{
		dest = find_env(env, "HOME");
		if (!dest)
			cd_error(NULL, "HOME not set", exc_data);
		return (dest);
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		dest = find_env(env, "OLDPWD");
		if (!dest)
			cd_error(NULL, "OLDPWD not set", exc_data);
		return (dest);
	}
	return (args[1]);
}

void	cd(char **args, char **env, t_exec *exc_data)
{
	char	*dest;

	exc_data->data->exit_status = 0;
	if (args[1] && ft_strncmp(args[1], "--", 3) == 0)
		args++;
	if (args_size(args) > 2)
	{
		cd_error(NULL, "too many arguments", exc_data);
		return ;
	}
	dest = cd_target(args, env, exc_data);
	if (!dest)
		return ;
	if (chdir(dest) == -1)
	{
		cd_error(dest, strerror(errno), exc_data);
		return ;
	}
	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
		ft_putendl_fd(dest, 1);
	pwd_update(env);
}
