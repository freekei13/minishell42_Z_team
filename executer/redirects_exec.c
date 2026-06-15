/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:56:05 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/20 16:38:10 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char *read_heredoc_line(void)
{
    char    buf[2];
    char    *line;
    char    *tmp;
    int     bytes;

    buf[1] = '\0';
    line = ft_strdup("");
    while (1)
    {
        bytes = read(0, buf, 1);
        if (bytes <= 0 || buf[0] == '\n')
            break ;
        tmp = line;
        line = ft_strjoin(tmp, buf);
        free(tmp);
    }
    if (bytes <= 0 && !*line)
   		return (free(line), NULL);
	if (bytes <= 0) 
    	return (line);
    return (line);
}

int	here_doc_loop(t_redirect *redirects, int *pipefd)
{
	char		*prompt;

	sigint_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		prompt = read_heredoc_line();
		if (!prompt)
		{
			if (g_status == 2)
			{
				g_status = 130;
				return (-2);
			}
			g_status = 0;
			return (-1);
		}
		if (ft_strncmp(prompt, redirects->file, 
				ft_strlen(redirects->file) + 1) == 0)
		{
			free(prompt);
			return (0);
		}
		ft_putstr_fd(prompt, pipefd[1]);
		ft_putstr_fd("\n", pipefd[1]);
		free(prompt);
	}
}

int	fds_redirects(t_ast *ast, int type)
{
	int	fd;
	
	if (type == REDIRECT_IN)
		fd = open(ast->data.cmd.redirects->file, O_RDONLY);
	else if (type == REDIRECT_OUT)
		fd = open(ast->data.cmd.redirects->file, O_WRONLY |
				O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(ast->data.cmd.redirects->file, O_WRONLY |
				O_CREAT | O_APPEND, 0644);
	else
			fd = -1;
	return (fd);
}

int	redirects(t_ast *ast, t_exec *data)
{
	while (ast->data.cmd.redirects)
	{
		if (ast->data.cmd.redirects->type == REDIRECT_IN)
		{
			data->fd_in = fds_redirects(ast, REDIRECT_IN);
			if (data->fd_in == -1)
				return (error_exit(1, NULL, ast, 1), -1);
		}
		else if (ast->data.cmd.redirects->type == HEREDOC)
		{
			data->fd_in = ast->data.cmd.redirects->fd;
		}
		else if (ast->data.cmd.redirects->type == REDIRECT_OUT)
		{
			data->fd_out = fds_redirects(ast, REDIRECT_OUT);
			if (data->fd_out == -1)
				return (error_exit(1, NULL, ast, 1), -1);
		}
		else if (ast->data.cmd.redirects->type == APPEND)
		{
			data->fd_out = fds_redirects(ast, APPEND);
			if (data->fd_out == -1)
				return (error_exit(1, NULL, ast, 1), -1);
		}
		ast->data.cmd.redirects = ast->data.cmd.redirects->next;
	}
	return (0);
}
