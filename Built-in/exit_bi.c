/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:44 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/23 23:51:42 by marvin           ###   ########.fr       */
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

void	numeric_err_print(char *arg, t_exec *exc_data)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exc_data->data->exit_status = 2;
}

int	numeric_check(char *arg, t_exec *exc_data)
{
	int					i;
	unsigned long long	res;
	int					sign;

	sign = 1;
	i = 0;
	res = 0;
	if (arg[0] == '\0')
		return (numeric_err_print(arg, exc_data), 1);
	while (arg[i])
	{
		if ((arg[i] == '-' || arg[i] == '+') && i == 0)
		{
			if (arg[i] == '-')
				sign *= -1;
			i++;
		}
		if (ft_isdigit(arg[i]) == 0)
			return (numeric_err_print(arg, exc_data), 1);
		res = res * 10 + (arg[i] - 48);
		if (res > 9223372036854775807ull && sign == 1)
			return (numeric_err_print(arg, exc_data), 1);
		else if (res > 9223372036854775808ull && sign == -1)
			return (numeric_err_print(arg, exc_data), 1);
		i++;
	}
	return (0);
}

void	exit_fct(t_ast *ast, char ***env, t_exec *exc_data)
{
	char		**arg;
	
	if (exc_data->is_child == 0 && isatty(STDIN_FILENO))
		printf("exit\n");
	arg = ast->data.cmd.args;
	if (arg[1] && numeric_check(arg[1], exc_data) == 1)
		exit(exc_data->data->exit_status);
	if (args_len(arg) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exc_data->data->exit_status = 1;
		return ;
	}
	if (args_len(arg) > 1)
		exc_data->data->exit_status = ft_atoi(arg[1]) % 256;
	free_ast(ast);
	split_free(*env);
	exit(exc_data->data->exit_status);
}
