/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/24 02:25:00 by marvin           ###   ########.fr       */
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
	argv[1] = NULL;
	while (1)
	{
		signal_set(data);
		// data.cmd = readline("minishell $ ");
		// if (!data.cmd)
		// {
		// 	printf("exit\n");
		// 	break ;
		// }
		// add_history(data.cmd);
		// ces ligne de code remplace l'ancien pour ajouter un test (isatty()) pour savoir
		// si fd en argument est connecte a un terminal reel
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
		// ./minishell                    # stdin = ton clavier, un vrai tty
		// ./minishell < fichier.txt       # stdin = un fichier
		// echo "ls" | ./minishell         # stdin = l'autre bout d'un pipe
		// Dans les deux derniers cas, il n'y a personne derrière le clavier pour lire un prompt ou taper une réponse
		tokens = tokenize(data.cmd, envp[0], data.exit_status);
		free(data.cmd);
		ast = parser(tokens);
		if (ast)
		{
			data.root_ast = ast;
			free_tokens(tokens);
			//print_ast(ast, 0);
			executer(ast, envp, &data, 0);
			free_ast(ast);
			ast = NULL;
		}
	}
	rl_clear_history();
	if (envp[0][0])
		split_free(envp[0]);
	free(envp);
	return (data.exit_status);
}
