/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:56:05 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/04 00:34:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	*read_heredoc_line(void)
{
	char	buf[2];
	char	*line;
	char	*tmp;
	int		bytes;

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

int	here_doc_loop(t_redirect *redirects, int *pipefd, t_exec exc_data)
{
	char	*prompt;

	sigint_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		prompt = read_heredoc_line();
		if (!prompt)
		{
			if (g_signal == 2)
			{
				exc_data.data->exit_status = 130;
				return (-2);
			}
			exc_data.data->exit_status = 0;
			return (-1);
		}
		if (ft_strncmp(prompt, redirects->file,
				ft_strlen(redirects->file) + 1) == 0)
			return (free(prompt), 0);
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
		fd = open(redirects->file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(redirects->file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

int	redirects(t_ast *ast, t_exec *exc_data)
{
	t_redirect	*rtmp;

	rtmp = ast->data.cmd.redirects;
	while (rtmp)
	{
		if (rtmp->type == REDIRECT_IN)
			exc_data->fd_in = fds_redirects(rtmp, REDIRECT_IN);
		else if (rtmp->type == HEREDOC)
			exc_data->fd_in = rtmp->fd;
		else if (rtmp->type == REDIRECT_OUT)
			exc_data->fd_out = fds_redirects(rtmp, REDIRECT_OUT);
		else if (rtmp->type == APPEND)
			exc_data->fd_out = fds_redirects(rtmp, APPEND);
		if ((rtmp->type == REDIRECT_IN || rtmp->type == HEREDOC)
			&& exc_data->fd_in == -1)
			return (error_exit(1, err_message_custom(rtmp->file,
						strerror(errno)), ast, exc_data), -1);
		if ((rtmp->type == REDIRECT_OUT || rtmp->type == APPEND)
			&& exc_data->fd_out == -1)
			return (error_exit(1, err_message_custom(rtmp->file,
						strerror(errno)), ast, exc_data), -1);
		rtmp = rtmp->next;
	}
	return (0);
}
