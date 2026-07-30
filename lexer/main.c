/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/30 03:30:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	data_init(t_data *data)
{
	data->cmd = NULL;
	data->exit_status = 0;
	data->pid = -1;
	data->root_ast = NULL;
	data->sigquit_flag = 0;
}

int	cmd_readline(t_data *data)
{
	if (isatty(STDIN_FILENO))
		data->cmd = readline("minishell $ ");
	else
		data->cmd = read_heredoc_line();
	if (!data->cmd)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		return (0);
	}
	if (isatty(STDIN_FILENO))
		add_history(data->cmd);
	return (1);
}

void	exec_proces(t_ast *ast, t_token *tokens, char ***envp, t_data *data)
{
	t_ast	*err;
	
	data->root_ast = ast;
	free_tokens(tokens);
	err = ast_find_error(ast);
	if (err)
	{
		ft_putstr_fd(err->u_data.err.err_message, 2);
		data->exit_status = err->u_data.err.status_code;
	}
	else
		executer(ast, envp, data, 0);
	free_ast(ast);
	ast = NULL;
}

int	main(int argc, char **argv, char **envi)
{
	t_token	*tokens;
	t_ast	*ast;
	char	**envp;
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (0);
	envp = make_env(envi);
	data_init(&data);
	while (1)
	{
		signal_set(&data);
		if (cmd_readline(&data) == 0)
			break ;
		tokens = tokenize(data.cmd, envp, data.exit_status);
		free(data.cmd);
		ast = parser(tokens);
		if (ast)
			exec_proces(ast, tokens, &envp, &data);
	}
	rl_clear_history();
	if (envp)
		split_free(envp);
	return (data.exit_status);
}
