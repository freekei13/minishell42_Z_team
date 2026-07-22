/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:07 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/23 00:45:32 by marvin           ###   ########.fr       */
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

// void	pwd_update(char **env, char *path, int i)
// {
// 	char	**pwd;
// 	char	*str;

// 	pwd = malloc(sizeof(char **) * 3);
// 	str = find_env(env, "PWD");
// 	if (ft_strcmp(path, find_env(env, "OLDPWD")) == 0)
// 		pwd[0] = ft_strjoin("PWD=", path);
// 	else
// 	{
// 		pwd[0] = ft_strjoin("PWD=", ft_strjoin(find_env(env, "PWD"),
// 			ft_strjoin("/", path)));
// 	}
// 	if (i == 0)
// 		pwd[1] = ft_strjoin("OLDPWD=", str);
// 	else
// 		pwd[1] = NULL;
// 	pwd[2] = NULL;
// 	env = chg_env(env, pwd);
// 	split_free(pwd);
// 	return ;
// }

void	cd_error(char *arg, char *msg, t_exec *exc_data)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	exc_data->data->exit_status = 1;
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
// void	pwd_dot_update(char **env, t_int i)
// {
// 	char	**pwd;
// 	char	*str;
// 	char	*cmp;

// 	str = malloc(sizeof(char *) * ft_strlen(find_env(env, "PWD")));
// 	cmp  = malloc(sizeof(char *) * ft_strlen(find_env(env, "PWD")));
// 	pwd = malloc(sizeof(char *) * 3);
// 	cmp = find_env(env, "PWD");
// 	i.is = ft_strlen(cmp) - 1;
// 	while(cmp[i.is] != '/')
// 		i.is--;
// 	i.i = -1;
// 	while(cmp[++i.i] && i.i < i.is)
// 		str[i.i] = cmp[i.i];
// 	str[i.i] = '\0';
// 	pwd[0] = ft_strjoin("PWD=", str);
// 	if (i.js == 0)
// 		pwd[1] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
// 	else
// 		pwd[1] = NULL;
// 	pwd[2] = NULL;
// 	env = chg_env(env, pwd);
// 	free(str);
// 	return ;
// }

// void	make_arg(char **arguments, char **arg, int dash)
// {
// 		arguments[0] = ft_strdup(arg[0]);
// 		if (arg[1][1])
// 			arguments[1] = ft_strdup(arg[1] + dash);
// 		else 
// 			arguments[1] = NULL;
// 		arguments[2] = NULL;
// }

// void	dot_cd(char **arg, char **env, t_int i, t_exec *exc_data)
// {
// 	char	**arguments;

// 	if (arg[1][0] == '.' && arg[1][1] == '.' &&
// 		(!arg[1][2] || arg[1][2] == '/'))
// 	{
// 		pwd_dot_update(env, i);
// 		arguments = malloc(sizeof(char *) * 2);
// 		make_arg(arguments, arg, 3);
// 		if (arguments && i.i != -1 && ++i.js)
// 			cd(arguments, env, exc_data, i);
// 		exc_data->data->exit_status = 0;
// 		split_free(arguments);
// 	}
// 	else if (arg[1][0] == '.' && (arg[1][1] == '\0'  || arg[1][1] == '/'))
// 	{
// 		arguments = malloc(sizeof(char *) * 2);
// 		make_arg(arguments, arg, 2);
// 		if (arguments && i.i != -1 && ++i.js)
// 			cd(arguments, env, exc_data, i);
// 		exc_data->data->exit_status = 0;
// 		split_free(arguments);
// 	}
// }

// void		cd(char **args, char **env, t_exec *exc_data, t_int i)
// {
// 	char	*str;
// 	int		fd;

// 	if (exc_data->fd_out == -1)
// 		fd = 1;
// 	else
// 		fd = exc_data->fd_out;
// 	exc_data->data->exit_status = 1;
// 	if (args_size(args) != 2)
// 		{
// 			ft_putstr_fd("cd : too many arguments\n", fd);
// 			return ;
// 		}
// 	if (args[1] && strncmp(args[1], "-", 2) == 0)
// 	{
// 		i.ks = chdir(find_env(env, "OLDPWD"));
// 		if (i.ks == 0)
// 			pwd_update(env, find_env(env, "OLDPWD"), i.js);
// 		else if (i.ks == -1)
// 		{
// 			ft_putstr_fd("cd: ", fd);
// 			ft_putstr_fd(args[1], fd);
// 			ft_putstr_fd(": No such file or directory\n", fd);
// 			return ;
// 		}
// 	}
// 	else if (args[1][0] == '.')
// 	{
// 		i.i = dash_lengh(args[1]);
// 		str = no_dash(args[1], i.i);
// 		if (i.i == -1)
// 			i.ks = chdir(args[1]);
// 		else
// 			i.ks = chdir(str);
// 		if (i.i != -1)
// 			free(str);
// 		if (i.ks == -1)
// 		{
// 			ft_putstr_fd("cd: ", fd);
// 			ft_putstr_fd(args[1], fd);
// 			ft_putstr_fd(": No such file or directory\n", fd);
// 			return ;
// 		}
// 		if (i.ks == 0)
// 		return (dot_cd(args, env, i, exc_data));
// 	}
// 	else
// 	{
// 		if (args[1][ft_strlen(args[1]) - 1] == '/')
// 			args[1][ft_strlen(args[1]) - 1] = '\0';
// 		i.ks = chdir(args[1]);
// 		if (i.ks == 0)
// 			pwd_update(env, args[1], i.js);
// 		else if (i.ks == -1)
// 		{
// 			ft_putstr_fd("cd: ", fd);
// 			ft_putstr_fd(args[1], fd);
// 			ft_putstr_fd(": No such file or directory\n", fd);
// 			return ;
// 		}

// 	}
// 	if (i.ks == 0)
// 		exc_data->data->exit_status = 0;
// 	return ;
// }
