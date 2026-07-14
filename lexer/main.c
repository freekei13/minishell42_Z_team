/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/14 11:57:50 by lalamino         ###   ########.fr       */
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
	char	***envp;
	t_data	data;

	if (argc == -1)
		return (0);
	envp = malloc(sizeof(char **) * 2);
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
		tokens = tokenize(data.cmd, envp[0], data.exit_status);
		free(data.cmd);
		ast = parser(tokens);
		if (ast)
		{
			data.root_ast = ast;
			free_tokens(tokens);
			//print_ast(ast, 0);
			executer(ast, envp[0], &data, 0);
			free_ast(ast);
			ast = NULL;
		}
		printf("Tmp: $? = %d\n", data.exit_status);
	}
	rl_clear_history();
	if (envp[0][0])
		split_free(envp[0]);
	free(envp);
	return (data.exit_status);
}
