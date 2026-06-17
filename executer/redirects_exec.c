/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:56:05 by csamakka          #+#    #+#             */
/*   Updated: 2026/06/17 01:03:09 by marvin           ###   ########.fr       */
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

int	fds_redirects(t_redirect *redirects, int type)
{
	int	fd;
	
	if (type == REDIRECT_IN)
		fd = open(redirects->file, O_RDONLY);
	else if (type == REDIRECT_OUT)
		fd = open(redirects->file, O_WRONLY |
				O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(redirects->file, O_WRONLY |
				O_CREAT | O_APPEND, 0644);
	else
			fd = -1;
	return (fd);
}

int	redirects(t_ast *ast, t_exec *data)
{
	t_redirect	*redirects_tmp;
	
	redirects_tmp = ast->data.cmd.redirects;
	while (redirects_tmp)
	{
		if (redirects_tmp->type == REDIRECT_IN)
		{
			data->fd_in = fds_redirects(redirects_tmp, REDIRECT_IN);
			if (data->fd_in == -1)
				return (error_exit(1, NULL, ast, 1), -1);
		}
		else if (redirects_tmp->type == HEREDOC)
			data->fd_in = redirects_tmp->fd;
		else if (redirects_tmp->type == REDIRECT_OUT)
		{
			data->fd_out = fds_redirects(redirects_tmp, REDIRECT_OUT);
			if (data->fd_out == -1)
				return (error_exit(1, NULL, ast, 1), -1);
		}
		else if (redirects_tmp->type == APPEND)
		{
			data->fd_out = fds_redirects(redirects_tmp, APPEND);
			if (data->fd_out == -1)
				return (error_exit(1, NULL, ast, 1), -1);
		}
		redirects_tmp = redirects_tmp->next;
	}
	return (0);
}
