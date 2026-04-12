/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:56:05 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 00:06:47 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	here_doc_loop(t_ast *ast, int *pipefd)
{
	char		*prompt;
	
	close(pipefd[0]);
	while (1)
	{
		prompt = readline(">");
		if (ft_strncmp(prompt, ast->data.cmd.redirects->file,
			ft_strlen(ast->data.cmd.redirects->file) + 1) == 0)
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

void	here_doc(t_ast *ast, t_exec *data)
{
	pid_t		pid;
	
	if (pipe(data->pipefd) == -1)
		return (error_exit(1, NULL, ast, 1));
	pid = fork();
	if (pid == -1)
		return (error_exit(1, NULL, ast, 1));
	if (pid == 0)
		here_doc_loop(ast, data->pipefd);
	close(data->pipefd[1]);
	data->fd_in = data->pipefd[0];
	waitpid(pid, NULL, 0);
}

void	redirects(t_ast *ast, t_exec *data)
{
	while (ast->data.cmd.redirects)
	{
		if (ast->data.cmd.redirects->type == REDIRECT_IN)
		{
			data->fd_in = open(ast->data.cmd.redirects->file, O_RDONLY);
			if (data->fd_in == -1)
				return (error_exit(1, NULL, ast, 1));
		}
		else if (ast->data.cmd.redirects->type == HEREDOC)
			here_doc(ast, data);
		else if (ast->data.cmd.redirects->type == REDIRECT_OUT)
		{
			data->fd_out = open(ast->data.cmd.redirects->file, O_WRONLY |
				O_CREAT | O_TRUNC, 0644);
			if (data->fd_out == -1)
				return (error_exit(1, NULL, ast, 1));
		}
		else if (ast->data.cmd.redirects->type == APPEND)
		{
			data->fd_out = open(ast->data.cmd.redirects->file, O_WRONLY |
				O_CREAT | O_APPEND, 0644);
			if (data->fd_out == -1)
				return (error_exit(1, NULL, ast, 1));
		}
		ast->data.cmd.redirects = ast->data.cmd.redirects->next;
	}
}
