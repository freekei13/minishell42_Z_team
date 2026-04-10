/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:35:03 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/11 01:34:51 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	executer(t_ast *ast, char **env)
{
	int			pipefd[2];
	int			fd_in;
	int			fd_out;
	
	fd_in = -1;
	fd_out = -1;
	if (ast->type == AST_CMD)
	{
		if (pipe(pipefd) == -1)
			error_exit(1, NULL, ast);
		redirects(ast, &fd_in, &fd_out, pipefd);
		pid_t	pid_cmd;
		
		pid_cmd = fork();
		if (pid_cmd == -1)
			error_exit(1, NULL, ast);
		if (pid_cmd == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_in);
			close(fd_out);
			//find path;
			if (execve("path", ast->data.cmd.args, env) == -1)
			{
				perror("minishell: ");
				//free tokens;
				//free ast;
				exit(errno);
			}
		}
		close(pipefd[1]);
		fd_in = pipefd[0];
		waitpid(pid_cmd, NULL, 0);
		
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
