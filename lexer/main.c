/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/06/24 17:49:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	g_signal;

void	data_init(t_data *data)
{
	g_signal = 0;
	data->exit_status = 0;
	data->pid = -1;
	data->root_ast = NULL;
}

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
	cm->data.cmd.args[1] = ft_strdup("pli=plier");
	cm->data.cmd.args[2] = ft_strdup("pla=plateau");
	// cm.data.cmd.args[1] = ft_strdup("barte");
	// cm.data.cmd.args[2] = ft_strdup("USER>tl");
	// cm.data.cmd.args[3] = ft_strdup("PWD");
	cm->data.cmd.args[3] = NULL;
	// printf("%s\n%s\n\n", find_env(env, "PWD"), find_env(env, "OLDPWD"));
	// printf("%s\n%s\n\n", find_env(env, "pli"), find_env(env, "barte"));
	// echo_fct(cm);
	// printf("\n\n%s\n", find_env(*env, "pli"));
	builtin(cmd, env);
	printf("%s\n", find_env(*env, "pli"));
	printf("%s\n", find_env(*env, "pla"));
	builtin(cmd, env);
	// env = add_env(env, cm->data.cmd.args);
	// env = chg_env(env, cm.data.cmd.args);
	// cd(cm.data.cmd.args, env);
	// printf("%s\n%s\n", find_env(env, "PWD"), find_env(env, "OLDPWD"));
	// printf("%s\n%s\n", find_env(env, "PWD"), find_env(env, "USER"));
	// printf("%s\n%s\n\n", find_env(env, "pli"), find_env(env, "barte"));
	// split_free(cm->data.cmd.args);

	//a voir pr fct
	//cd
	//export -> unset
}

int	main(int argc, char **argv, char **envi)
{
	t_token	*tokens;
	t_ast	*ast;
	char	***envp;
	t_data	data;

	if (argc == -1)
		return (0);
	envp = malloc(sizeof(char ***) * 2);
	envp[0] = make_env(envi);
	envp[1] = NULL;
	data_init(&data);
	// printf("%s\n%s\n", find_env(envp[0], "PWD"), find_env(envp[0], "OLDPWD"));
	// btin_test(envp);
	// printf("%s\n%s\n", find_env(envp[0], "PWD"), find_env(envp[0], "OLDPWD"));
	// printf("%s\n%s\n", find_env(envp[0], "pli"), find_env(envp[0], "pla"));

	argv[1] = NULL;
	while (1)
	{
		signal_set(data);
		data.cmd = readline("minishell $ ");
		if (!data.cmd)
		{
			printf("exit\n");
			break ;
		}
		add_history(data.cmd);
		tokens = tokenize(data.cmd, envp[0]);
		free(data.cmd);
		ast = parser(tokens);
		if (!ast)
			break ;
		data.root_ast = ast;
		free_tokens(tokens);
		//print_ast(ast, 0);
		executer(ast, envp[0], &data, 0);
		free_ast(ast);
		ast = NULL;
	}
	rl_clear_history();
	if (envp[0][0])
		split_free(envp[0]);
	free(envp);
	return (0);
}
