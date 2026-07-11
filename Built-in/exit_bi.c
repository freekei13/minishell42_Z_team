/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:44 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/11 02:44:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	args_len(char **arg)
{
	int i;
	
	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	exit_fct(t_ast *ast, char ***env, t_exec *exc_data)
{
	char		**arg;
	int			i;
	long long	res;
	
	printf("exit\n");
	arg = ast->data.cmd.args;
	i = 0;
	res = 0;
	while (arg[1] && arg[1][i])
	{
		if (i == 0)
		{
			if (arg[1][i] == '-' || arg[1][i] == '+')
				i++;
		}
		if (arg[1][0] == '\0' || ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exc_data->data->exit_status = 2;
			return ;
		}
		res = res * 10 + (arg[1][i] - 48);
		i++;
	}
	if (arg[1][0] == '\0')
		printf("FOUND\n");
	if (args_len(arg) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exc_data->data->exit_status = 2;
		return ;
	}
	if (args_len(arg) > 1)
		exc_data->data->exit_status = ft_atoi(arg[1]) % 256;
	free_ast(ast);
	split_free(*env);
	exit(exc_data->data->exit_status);
}
