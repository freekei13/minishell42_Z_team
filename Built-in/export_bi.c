/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:22 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/30 21:31:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	args_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	sort_env(char **tab)
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

void	print_export(char **env)
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
		if (j != 1 || cp[i][0] != '_')
			print_export_line(cp[i], j);
	}
	split_free(cp);
}

void	export_one(char ***env, char *arg)
{
	char	*name;
	char	*tab[2];
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (arg[len] != '=')
		return ;
	if (len > 0 && arg[len - 1] == '+')
	{
		name = append_arg(*env, arg, len);
		if (name)
			export_one(env, name);
		free(name);
		return ;
	}
	name = ft_substr(arg, 0, len);
	tab[0] = arg;
	tab[1] = NULL;
	if (find_env(*env, name) != NULL)
		*env = chg_env(*env, tab);
	else
		*env = add_env(*env, tab);
	free(name);
}

void	export(char ***env, char **cmd, t_exec *exc_data)
{
	int	i;
	int	ret;
	
	exc_data->data->exit_status = 0;
	if (!cmd[0])
	{
		return (print_export(*env));
	}
	i = -1;
	while (cmd[++i])
	{
		ret = is_valid_id(cmd[i]);
		if (ret == 1)
		{
			id_error("export", cmd[i]);
			exc_data->data->exit_status = 1;
		}
		else if (ret == 2)
		{
			option_error("export", cmd[i]);
			exc_data->data->exit_status = 2;
		}
		else
			export_one(env, cmd[i]);
	}
}
