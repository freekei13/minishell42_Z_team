/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:56:05 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/26 03:56:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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

void	fds_set(t_redirect *rtmp, t_exec *exc_data)
{
	if (rtmp->type == REDIRECT_IN)
	{
		if (exc_data->fd_in != -1)
			close(exc_data->fd_in);
		exc_data->fd_in = fds_redirects(rtmp, REDIRECT_IN);
	}
	else if (rtmp->type == HEREDOC)
	{
		if (exc_data->fd_in != -1)
			close(exc_data->fd_in);
		exc_data->fd_in = rtmp->fd;
	}
	else if (rtmp->type == REDIRECT_OUT)
	{
		if (exc_data->fd_out != -1)
			close(exc_data->fd_out);
		exc_data->fd_out = fds_redirects(rtmp, REDIRECT_OUT);
	}
	else if (rtmp->type == APPEND)
	{
		if (exc_data->fd_out != -1)
			close(exc_data->fd_out);
		exc_data->fd_out = fds_redirects(rtmp, APPEND);
	}
}

int	redirects(t_ast *ast, t_exec *exc_data)
{
	t_redirect	*rtmp;

	rtmp = ast->u_data.cmd.redirects;
	while (rtmp)
	{
		fds_set(rtmp, exc_data);
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
