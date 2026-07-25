/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/25 02:22:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	g_signal;

void	data_init(t_data *data)
{
	data->exit_status = 0;
	data->pid = -1;
	data->root_ast = NULL;
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
		signal_set(data);
		if (isatty(STDIN_FILENO)) 
			data.cmd = readline("minishell $ ");
		else
			data.cmd = read_heredoc_line();
		if (!data.cmd)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (isatty(STDIN_FILENO))
			add_history(data.cmd);
		tokens = tokenize(data.cmd, envp, data.exit_status);
		free(data.cmd);
		ast = parser(tokens);
		if (ast)
		{
			data.root_ast = ast;
			free_tokens(tokens);
			executer(ast, &envp, &data, 0);
			free_ast(ast);
			ast = NULL;
		}
	}
	rl_clear_history();
	if (envp[0])
		split_free(envp);
	return (data.exit_status);
}
