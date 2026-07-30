/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:48:30 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/30 02:47:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**bi_names(void)
{
	char	**names;
	int		i;

	i = -1;
	names = malloc(sizeof(char **) * 8);
	names[++i] = "cd";
	names[++i] = "echo";
	names[++i] = "env";
	names[++i] = "exit";
	names[++i] = "export";
	names[++i] = "pwd";
	names[++i] = "unset";
	names[++i] = NULL;
	return (names);
}

int	keep_builtin(t_ast *cmd, char ***env, t_int i, t_exec *exc_data)
{
	if (i.js == 2)
	{
		if (!cmd->u_data.cmd.args[1])
			env_bi(*env, exc_data);
		else
			exc_data->data->exit_status = 127;
	}
	else if (i.js == 3)
		exit_fct(cmd, *env, exc_data);
	else if (i.js == 4)
		export(env, cmd->u_data.cmd.args + 1, exc_data);
	else if (i.js == 5)
		pwd(*env, exc_data);
	else if (i.js == 6)
		unset(env, cmd->u_data.cmd.args + 1, exc_data);
	return (exc_data->data->exit_status);
}

int	echo_opt(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin(t_ast *cmd, char ***env, t_exec *exc_data)
{
	char	**names;
	t_int	i;

	names = bi_names();
	i.js = 0;
	while (names[i.js] && ft_strncmp(cmd->u_data.cmd.args[0],
			names[i.js], ft_strlen(names[i.js]) + 1) != 0)
		i.js++;
	if (i.js >= 7)
		return (free(names), 1);
	if (i.js == 0)
		cd(cmd->u_data.cmd.args, *env, exc_data);
	else if (i.js == 1)
	{
		i.i = 0;
		while (cmd->u_data.cmd.args[1 + i.i]
			&& echo_opt(cmd->u_data.cmd.args[1 + i.i]))
			i.i++;
		if (i.i > 0)
			echo_fct(cmd->u_data.cmd.args + 1 + i.i, 1, exc_data);
		else if (cmd->u_data.cmd.args[1])
			echo_fct(cmd->u_data.cmd.args + 1, 0, exc_data);
		else
			echo_fct(NULL, 0, exc_data);
	}
	keep_builtin(cmd, env, i, exc_data);
	free(names);
	return (0);
}
