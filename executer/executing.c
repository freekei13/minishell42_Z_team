/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:35:03 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/08 01:38:24 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	here_doc(char *e_o_f, int *fd_in, int *pipefd)
{
	pid_t		pid;
	char		*prompt;
	
	if (pipe(pipefd) == -1)
	{
		perror("minishell: ");
		//free tokens;
		//free ast;
		exit (errno);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: ");
		//free tokens;
		//free ast;
		exit(errno);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			prompt = readline(">");
			if (ft_strncmp(prompt, e_o_f, ft_strlen(prompt)) == 0
				&& ft_strlen(e_o_f) == ft_strlen(prompt))
			{
				free(prompt);
				close(pipefd[1]);
				exit(0);
			}
			ft_putstr_fd(prompt, pipefd[1]);
			ft_putstr_fd("\n", pipefd[1]);
			free(prompt);
		}
	}
	close(pipefd[1]);
	fd_in = pipefd[0];
	waitpid(pid, NULL, 0);
}

void	executer(t_ast *ast)
{
	t_redirect	*head;
	int			pipefd[2];
	int			fd_in;
	
	
	fd_in = -1;
	if (ast->type == AST_CMD)
	{
		if (ast->data.cmd.redirects)
		{
			head = ast->data.cmd.redirects;
			while (ast->data.cmd.redirects)
			{
				if (ast->data.cmd.redirects->type == HEREDOC)
					here_doc(ast->data.cmd.redirects->file, &fd_in, pipefd[2]);
				ast->data.cmd.redirects = ast->data.cmd.redirects->next;
			}
			ast->data.cmd.redirects = head;
			while (ast->data.cmd.redirects)
			{
				if (ast->data.cmd.redirects->type == REDIRECT_IN)
				{

				}
				ast->data.cmd.redirects = ast->data.cmd.redirects->next;
			}
		}
	}
	else if (ast->type == AST_PIPE)
	{
		//execute left d'abord puis right
		printf("PIPE\n");
	}
	else if (ast->type == AST_ERROR)
	{
		//handle error
		printf("ERROR\n");
	}
}
