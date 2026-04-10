/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:14 by csamakka          #+#    #+#             */
/*   Updated: 2026/03/30 18:33:31 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_token	*tokens;
	char	**env;

	if (argc == -1)
		return (0);
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
		while (tokens != NULL)
		{
			printf("Value : %s\nType : %d\n\n", tokens->value, tokens->type);
			tokens = tokens->next;
		}
	}
	int	i = -1;
	split_free(env);
	return (0);
}
