/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:48:30 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/10 17:02:02 by marvin           ###   ########.fr       */
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

int	keep_builtin(t_ast *cmd, char ***env, int i, t_exec *exc_data)
{
	if (i == 3) //exit
	{
		exit_fct(cmd, env, exc_data);
	}
	else if (i == 4)
		export(env, cmd->data.cmd.args + 1, exc_data);
	else if (i == 5)
		pwd(*env, exc_data);
	else if (i == 6)
		unset(env, cmd->data.cmd.args + 1, exc_data);
	return(exc_data->data->exit_status);
}

int	builtin(t_ast *cmd, char ***env, t_exec *exc_data)
{
	char	**names;
	int		i;

	names = bi_names();
	i = 0;
	while(names[i] && strcmp(cmd->data.cmd.args[0], names[i]) != 0)
		i++;
	if (i >= 7)
		return(1);
	if (i == 0)
	{
		if (!cmd->data.cmd.args[2] && cmd->data.cmd.args[1])
			cd(cmd->data.cmd.args, *env, exc_data);
	}
	else if (i == 1)
	{
		if (cmd->data.cmd.args[1] && strcmp(cmd->data.cmd.args[1], "-n") == 0)
			echo_fct(cmd->data.cmd.args + 2, 1, exc_data);
		else if (cmd->data.cmd.args[1])
			echo_fct(cmd->data.cmd.args + 1, 0, exc_data);
		else
			echo_fct(NULL, 0, exc_data);
	}
	else if (i == 2)
	{
		if (!cmd->data.cmd.args[1])
			env_bi(*env, exc_data);
	}
	keep_builtin(cmd, env, i, exc_data);
	free(names);
	return(0);
}
