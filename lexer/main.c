/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/21 11:49:11 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "executing.h"

void	btin_test(char **env)
{
	t_ast cm;
	cm.data.cmd.args = malloc(1000);
	cm.data.cmd.args[0] = ft_strdup("PWD");
	cm.data.cmd.args[1] = ft_strdup("barte");
	cm.data.cmd.args[2] = ft_strdup("USER");
	cm.data.cmd.args[3] = ft_strdup("PWD");
	cm.data.cmd.args[4] = NULL;
	printf("%s\n%s\n", find_env(env, "PWD"), find_env(env, "USER"));
	printf("%s\n%s\n\n", find_env(env, "pli"), find_env(env, "barte"));
	env = unset(env, cm);
	printf("%s\n%s\n", find_env(env, "PWD"), find_env(env, "USER"));
	printf("%s\n%s\n\n", find_env(env, "pli"), find_env(env, "barte"));
	split_free(cm.data.cmd.args);
}

int	main(int argc, char **argv, char **envi)
{
	char	*cmd;
	t_token	*tokens;
	t_ast	*ast;
	char	**envp;

	if (argc == -1)
		return (0);
	envp = make_env(envi);
	btin_test(envp);
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
