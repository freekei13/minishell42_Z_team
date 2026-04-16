/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/16 13:49:31 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "executing.h"

int	main(int argc, char **argv, char **envi)
{
	char	*cmd;
	t_token	*tokens;
	t_ast	*ast;
	char	**envp;

	if (argc == -1)
		return (0);
	envp = make_env(envi);
	argv[1] = NULL;
	while (1)
	{
		cmd = readline("minishell $");
		if (!cmd)
			break ;
		add_history(cmd);
		tokens = tokenize(cmd, envp);
		free(cmd);
		ast = parser(tokens);
		free_tokens(tokens);
		print_ast(ast, 0);
		executer(ast, envp);
		free_ast(ast);
		ast = NULL;
	}
	rl_clear_history();
	if (envp)
		split_free(envp);
	return (0);
}
