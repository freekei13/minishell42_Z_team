/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/12 13:51:10 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

int	g_status = 0;

void	sigdata_init(t_sigdata *sigdata)
{
	sigdata->exit_status = 0;
	sigdata->pid = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_sigdata	sigdata;
	t_token		*tokens;
	t_ast		*ast;
	char		**env;

	if (argc == -1)
		return (0);
	env = make_env(envp);
	argv[1] = NULL;
	while (1)
	{
		sigdata_init(&sigdata);
		signal_set(sigdata);
		sigdata.cmd = readline("minishell $");
		if (!sigdata.cmd)
			break ;
		add_history(sigdata.cmd);
		tokens = tokenize(sigdata.cmd, env);
		free(sigdata.cmd);
		ast = parser(tokens);
		free_tokens(tokens);
		print_ast(ast, 0);
		executer(ast, env, &sigdata);
		free_ast(ast);
		ast = NULL;
	}
	rl_clear_history();
	split_free(env);
	return (0);
}
