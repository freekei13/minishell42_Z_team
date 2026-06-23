/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:48:30 by lalamino          #+#    #+#             */
/*   Updated: 2026/06/22 14:30:36 by lalamino         ###   ########.fr       */
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

int	keep_builtin(t_ast *cmd, char ***env, int i, int nberr)
{
	if (i == 3) //exit
	{
		
	}
	else if (i == 4)
		export(env, cmd->data.cmd.args + 1);
	else if (i == 5)
		pwd(*env);
	else if (i == 6)
		unset(env, cmd->data.cmd.args + 1);
	else if (i == 7) //not Built-in
	{
		
	}
	return(nberr);
}

int	builtin(t_ast *cmd, char ***env)
{
	char	**names;
	int		i;
	int		nberr;

	names = bi_names();
	i = 0;
	while(names[i] && strcmp(cmd->data.cmd.args[0], names[i]) != 0)
		i++;
	if (i >= 7)
		return(1);
	if (i == 0)
	{
		if (!cmd->data.cmd.args[2] && cmd->data.cmd.args[1])
			nberr = cd(cmd->data.cmd.args, *env);
	}
	else if (i == 1)
	{
		if (strcmp(cmd->data.cmd.args[1], "-n") == 0)
			echo_fct(cmd->data.cmd.args + 2, 1);
		else
			echo_fct(cmd->data.cmd.args + 1, 0);
	}
	else if (i == 2)
	{
		if (!cmd->data.cmd.args[1])
			env_bi(*env);
	}
	nberr = keep_builtin(cmd, env, i, 0);
	//errhandle(nberr);
	free(names);
	return(0);
}
