/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/19 14:46:44 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "executing.h"

void	btin_test(char ***env)
{
	t_ast *cm;
	t_ast	*cmd;
	cmd = malloc(100);
	cmd->data.cmd.args = malloc(1000);
	cmd->data.cmd.args[0] = ft_strdup("unset");
	cmd->data.cmd.args[1] = ft_strdup("pli");
	cmd->data.cmd.args[2] = ft_strdup("pla");
	cmd->data.cmd.args[3] = NULL;
	cm = malloc(100);
	cm->data.cmd.args = malloc(1000);
	cm->data.cmd.args[0] = ft_strdup("export");
	cm->data.cmd.args[1] = ft_strdup("pli=123");
	cm->data.cmd.args[2] = ft_strdup("pla=321");
	// cm.data.cmd.args[1] = ft_strdup("barte");
	// cm.data.cmd.args[2] = ft_strdup("USER>tl");
	// cm.data.cmd.args[3] = ft_strdup("PWD");
	cm->data.cmd.args[3] = NULL;
	// printf("%s\n%s\n\n", find_env(env, "PWD"), find_env(env, "OLDPWD"));
	// printf("%s\n%s\n\n", find_env(env, "pli"), find_env(env, "barte"));
	// echo_fct(cm);
	builtin(cm, env);
	builtin(cmd, env);
	// env = add_env(env, cm->data.cmd.args);
	// env = chg_env(env, cm.data.cmd.args);
	// cd(cm.data.cmd.args, env);
	// printf("%s\n%s\n", find_env(env, "PWD"), find_env(env, "OLDPWD"));
	// printf("%s\n%s\n", find_env(env, "PWD"), find_env(env, "USER"));
	// printf("%s\n%s\n\n", find_env(env, "pli"), find_env(env, "barte"));
	// split_free(cm->data.cmd.args);
}

int	main(int argc, char **argv, char **envi)
{
	char	*cmd;
	t_token	*tokens;
	t_ast	*ast;
	char	***envp;

	if (argc == -1)
		return (0);
	envp = malloc(sizeof(char ***) * 2);
	envp[0] = make_env(envi);
	envp[1] = NULL;
	printf("%s\n%s\n", find_env(envp[0], "pli"), find_env(envp[0], "pla"));
	btin_test(envp);
	printf("%s\n%s\n", find_env(envp[0], "pli"), find_env(envp[0], "pla"));
	argv[1] = NULL;
	while (1)
	{
		cmd = readline("minishell $");
		if (!cmd)
			break ;
		add_history(cmd);
		tokens = tokenize(cmd, envp[0]);
		free(cmd);
		ast = parser(tokens);
		free_tokens(tokens);
		print_ast(ast, 0);
		echo_fct(ast->data.cmd.args, 1);
		executer(ast, envp[0]);
		free_ast(ast);
		ast = NULL;
	}
	rl_clear_history();
	if (envp[0][0])
		split_free(envp[0]);
	free(envp);
	return (0);
}
