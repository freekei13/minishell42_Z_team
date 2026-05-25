/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/20 15:39:01 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

int	g_status;

void	sigdata_init(t_sigdata *sigdata)
{
	g_status = 0;
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
	sigdata_init(&sigdata);
	argv[1] = NULL;
	while (1)
	{
		signal_set(sigdata);
		sigdata.cmd = readline("minishell $ ");
		if (!sigdata.cmd)
		{
			printf("exit\n");
			break ;
		}
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
