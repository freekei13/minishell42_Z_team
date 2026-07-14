/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:07 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/14 12:37:07 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "builtin.h"

// int	cdERR(char **args)
// {
	
// }

void	pwd_update(char **env, char *path, int i)
{
	char	**pwd;
	char	*str;

	pwd = malloc(sizeof(char **) * 3);
	str = find_env(env, "PWD");
	if (ft_strcmp(path, find_env(env, "OLDPWD")) == 0)
		pwd[0] = ft_strjoin("PWD=", path);
	else
	{
		pwd[0] = ft_strjoin("PWD=", ft_strjoin(find_env(env, "PWD"),
			ft_strjoin("/", path)));
	}
	if (i == 0)
		pwd[1] = ft_strjoin("OLDPWD=", str);
	else
		pwd[1] = NULL;
	pwd[2] = NULL;
	env = chg_env(env, pwd);
	split_free(pwd);
	return ;
}

void	pwd_dot_update(char **env, t_int i)
{
	char	**pwd;
	char	*str;
	char	*cmp;

	str = malloc(sizeof(char *) * ft_strlen(find_env(env, "PWD")));
	cmp  = malloc(sizeof(char *) * ft_strlen(find_env(env, "PWD")));
	pwd = malloc(sizeof(char *) * 3);
	cmp = find_env(env, "PWD");
	i.is = ft_strlen(cmp) - 1;
	while(cmp[i.is] != '/')
		i.is--;
	i.i = -1;
	while(cmp[++i.i] && i.i < i.is)
		str[i.i] = cmp[i.i];
	str[i.i] = '\0';
	pwd[0] = ft_strjoin("PWD=", str);
	if (i.js == 0)
		pwd[1] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
	else
		pwd[1] = NULL;
	pwd[2] = NULL;
	env = chg_env(env, pwd);
	free(str);
	return ;
}

void	make_arg(char **arguments, char **arg)
{
		arguments[0] = ft_strdup(arg[0]);
		arguments[1] = ft_strdup(arg[1] + 3);
		arguments[2] = NULL;
}

void	dot_cd(char **arg, char **env, t_int i, t_exec *exc_data)
{
	char	**arguments;

	if (arg[1][0] == '.' && arg[1][1] == '.' &&
		(!arg[1][2] || arg[1][2] == '.' || arg[1][2] == '/'))
	{
		pwd_dot_update(env, i);
		arguments = malloc(sizeof(char *) * 2);
		make_arg(arguments, arg);
		if (arguments && i.i != -1 && ++i.js)
			cd(arguments, env, exc_data, i);
		exc_data->data->exit_status = 0;
		split_free(arguments);
	}
}

void		cd(char **args, char **env, t_exec *exc_data, t_int i)
{
	char	*str;
	
	exc_data->data->exit_status = 1;
	if (args_size(args) != 2)
		return ;
	if (args[1] && strncmp(args[1], "-", 2) == 0)
	{
		i.ks = chdir(find_env(env, "OLDPWD"));

		if (i.ks == 0)
			pwd_update(env, find_env(env, "OLDPWD"), i.js);
		else if (i.ks == -1)
			return ;
	}
	else if (args[1][0] == '.')
	{
		i.i = dash_lengh(args[1]);
		str = no_dash(args[1], i.i);
		if (i.i == -1)
			i.ks = chdir(args[1]);
		else
			i.ks = chdir(str);
		if (i.i != -1)
			free(str);
		if (i.ks == -1)
			return ;
		if (i.ks == 0)
		return (dot_cd(args, env, i, exc_data));
	}
	else
	{
		if (args[1][ft_strlen(args[1]) - 1] == '/')
			args[1][ft_strlen(args[1]) - 1] = '\0';
		i.ks = chdir(args[1]);
		if (i.ks == 0)
			pwd_update(env, args[1], i.js);
		else if (i.ks == -1)
			return ;

	}
	if (i.ks == 0)
		exc_data->data->exit_status = 0;
	return ;
}
