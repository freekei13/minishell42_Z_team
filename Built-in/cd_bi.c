/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:07 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/06 11:21:22 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "builtin.h"

// int	cdERR(char **args)
// {
	
// }

void	pwd_update(char **env, char *path)
{
	char	**pwd;

	pwd = malloc(sizeof(char **) * 3);
	pwd[0] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
	if (ft_strcmp(path, find_env(env, "OLDPWD")) == 0)
		pwd[1] = ft_strjoin("PWD=", path);
	else
	{
		pwd[1] = ft_strjoin("PWD=", ft_strjoin(find_env(env, "PWD"),
			ft_strjoin("/", path)));
	}
	pwd[2] = NULL;
	env = chg_env(env, pwd);
	split_free(pwd);
	return ;
}

void	pwd_dot_update(char **env)
{
	char	**pwd;
	char	*str;
	char	*cmp;
	t_int		i;

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
	pwd[0] = ft_strjoin("OLDPWD=", find_env(env, "PWD"));
	pwd[1] = ft_strjoin("PWD=", str);
	pwd[2] = NULL;
	env = chg_env(env, pwd);
	printf("CMP : %s \nPWD : %s\nOLDPWD : %s\n\n", cmp, pwd[1], pwd[0]);
	free(str);
	//free(cmp);
	//split_free(pwd);
	return ;
}

char	*no_dash(char *arg, int x)
{
	char	*str;
	int		i;

	i = -1;
	if (x != -1)
	{
		str = malloc(sizeof(char *) * (x + 1));
		while (arg[++i] && arg[i] != '/')
			str[i] = arg[i];
		str[i] = '\0';
		return(str);
	}
	else
		return(NULL);
}

int	dot_cd(char **arg, char **env, t_int i)
{
	char	*str;
	char	**arguments;

	if (arg[1][0] == '.' && arg[1][1] == '.' &&
		(!arg[1][2] || arg[1][2] == '.' || arg[1][2] == '/'))
	{
		i.i = dash_lengh(arg[1]);
		str = no_dash(arg[1], i.i);
		if (i.i == -1)
			i.ks = chdir(arg[1]);
		else
			i.ks = chdir(str);
		if (i.ks == -1)
			return(1);
		if (i.i != -1)
			free(str);
		pwd_dot_update(env);
		arguments = malloc(sizeof(char *) * 2);
		arguments[0] = ft_strdup(arg[0]);
		arguments[1] = ft_strdup(arg[1] + 3);
		arguments[2] = NULL;
		i.j = 0;
		if (arguments && i.i != -1)
			i.j = cd(arguments, env);
		split_free(arguments);
		return(i.j);
	}
	return (1);
}

int		cd(char **args, char **env)
{
	t_int	i;

	i.js = 0;
	if (args_size(args) != 2)
		return (1);
	if (args[1] && strncmp(args[1], "-", 2) == 0)
	{
		i.ks = chdir(find_env(env, "OLDPWD"));
		if (i.ks == 0)
			pwd_update(env, find_env(env, "OLDPWD"));
		else if (i.ks == -1)
			return (1);
	}
	else if (args[1][0] == '.')
		return (dot_cd(args, env, i));
	else
	{
		i.ks = chdir(args[1]);
		if (i.ks == 0)
			pwd_update(env, args[1]);
		else if (i.ks == -1)
			return (1);
	}
	return (0);
}
