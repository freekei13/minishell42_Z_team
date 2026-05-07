/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/07 19:26:07 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_token	*tokens;
	t_ast	*ast;
	char	**env;

	if (argc == -1)
		return (0);
	signal_set();
	env = make_env(envp);
	argv[1] = NULL;
	while (1)
	{
		cmd = readline("minishell $");
		if (!cmd)
			break ;
		add_history(cmd);
		tokens = tokenize(cmd, env);
		free(cmd);
		ast = parser(tokens);
		free_tokens(tokens);
		print_ast(ast, 0);
		executer(ast, env);
		free_ast(ast);
		ast = NULL;
	}
	rl_clear_history();
	split_free(env);
	return (0);
}
