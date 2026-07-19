/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:22 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/19 03:26:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// void	export2(char ***env, char **valid_find, t_int i, char **cmd)
// {
// 	char	**valid_add;
// 	char	**valid_chg;

// 	i.i = 0;
// 	while (valid_find[i.i])
// 		i.i++;
// 	valid_add = malloc(sizeof(char *) * (i.i + 1));
// 	valid_chg = malloc(sizeof(char *) * (i.i + 1));
// 	i.i = -1;
// 	i.j = -1;
// 	i.k = -1;
// 	while (valid_find[++i.i])
// 	{
// 		if (find_env(*env, valid_find[i.i]) != NULL)
// 			valid_chg[++i.j] = ft_strdup(cmd[i.i]);
// 		else if (find_env(*env, valid_find[i.i]) == NULL)
// 			valid_add[++i.k] = ft_strdup(cmd[i.i]);
// 	}
// 	valid_chg[++i.j] = NULL;
// 	valid_add[++i.k] = NULL;
// 	env = add_env(env, valid_add);
// 	*env = chg_env(*env, valid_chg);
// 	return ;
// }

int	args_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

// void	export(char ***env, char **cmd, t_exec *exc_data)
// {
// 	char	**valid_find;
// 	t_int	i;

// 	exc_data->data->exit_status = 0;
// 	i.k = args_size(cmd);
// 	valid_find = malloc(sizeof(char *) * (i.k + 1));
// 	i.i = -1;
// 	i.j = -1;
// 	while (cmd[++i.i])
// 	{
// 		i.is = 0;
// 		if (cmd[i.i][0])
// 		{
// 			while (cmd[i.i][i.is]
// 					&& cmd[i.i][i.is] != '=')
// 				i.is++;
// 			if (cmd[i.i][i.is] == '=')
// 				valid_find[++i.j] = ft_substr(cmd[i.i], 0, i.is);
// 			else
// 				valid_find[++i.j] = ft_strdup(cmd[i.i]);
// 		}
// 	}
// 	valid_find[++i.j] = NULL;
// 	export2(env, valid_find, i, cmd);
// 	return ;
// }

#include "builtin.h"

static void	sort_env(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (tab[++i])
	{
		j = i;
		while (tab[++j])
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[j]) + 1) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

static void	print_export(char **env)
{
	char	**cp;
	int		i;
	int		j;

	cp = make_env(env);
	sort_env(cp);
	i = -1;
	while (cp[++i])
	{
		j = 0;
		while (cp[i][j] && cp[i][j] != '=')
			j++;
		ft_putstr_fd("declare -x ", 1);
		if (!cp[i][j])
			ft_putendl_fd(cp[i], 1);
		else
		{
			write(1, cp[i], j + 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(cp[i] + j + 1, 1);
			ft_putendl_fd("\"", 1);
		}
	}
	split_free(cp);
}

static void	export_one(char ***env, char *arg)
{
	char	*name;
	char	*tab[2];
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (arg[len] != '=')
		return ;
	name = ft_substr(arg, 0, len);
	tab[0] = arg;
	tab[1] = NULL;
	if (find_env(*env, name) != NULL)
		*env = chg_env(*env, tab);
	else
		add_env(env, tab);
	free(name);
}

void	export(char ***env, char **cmd, t_exec *exc_data)
{
	int	i;

	exc_data->data->exit_status = 0;
	if (!cmd[0])
	{
		print_export(*env);
		return ;
	}
	i = -1;
	while (cmd[++i])
	{
		if (!is_valid_id(cmd[i]))
		{
			id_error("export", cmd[i]);
			exc_data->data->exit_status = 1;
		}
		else
			export_one(env, cmd[i]);
	}
}