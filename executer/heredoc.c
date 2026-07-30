/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 03:18:32 by marvin            #+#    #+#             */
/*   Updated: 2026/07/26 03:18:32 by marvin           ###   ########.fr       */
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

int	here_doc_signal_handle(struct termios *term_save, t_exec *exc_data)
{
	tcsetattr(STDIN_FILENO, TCSANOW, term_save);
	if (g_signal == 2)
	{
		exc_data->data->exit_status = 130;
		return (-2);
	}
	exc_data->data->exit_status = 0;
	return (-1);
}

int	here_doc_loop(t_redirect *redirects, int *pipefd, t_exec exc_data)
{
	char			*prompt;
	struct termios	term_save;
	struct termios	term_new;

	sigint_heredoc();
	tcgetattr(STDIN_FILENO, &term_save);
	term_new = term_save;
	term_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_new);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "> ", 2);
		prompt = read_heredoc_line();
		if (!prompt)
			return (here_doc_signal_handle(&term_save, &exc_data));
		if (ft_strncmp(prompt, redirects->file,
				ft_strlen(redirects->file) + 1) == 0)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &term_save);
			return (free(prompt), 0);
		}
		ft_putstr_fd(prompt, pipefd[1]);
		ft_putstr_fd("\n", pipefd[1]);
		free(prompt);
	}
}

int	heredoc_ast_cmd(t_redirect *redirects, int *pipefd, t_exec exc_data)
{
	int	ret;

	while (redirects)
	{
		if (redirects->type == HEREDOC)
		{
			if (pipe(pipefd) == -1)
				return (0);
			ret = here_doc_loop(redirects, pipefd, exc_data);
			close(pipefd[1]);
			if (ret == -2)
				return (-2);
			if (ret == -1)
			{
				write(2, EOF_M, 58);
				ft_putstr_fd(redirects->file, 2);
				ft_putstr_fd("')\n", 2);
				redirects->fd = pipefd[0];
				return (-1);
			}
			redirects->fd = pipefd[0];
		}
		redirects = redirects->next;
	}
	return (0);
}

int	heredoc_handle(t_ast *ast, t_exec exc_data)
{
	int				pipefd[2];
	t_redirect		*redirects_tmp;
	int				ret;

	if (!ast)
		return (0);
	if (ast->e_type == AST_PIPE)
	{
		ret = heredoc_handle(ast->u_data.pipe.left, exc_data);
		if (ret == -2)
			return (-2);
		ret = heredoc_handle(ast->u_data.pipe.right, exc_data);
		if (ret == -2)
			return (-2);
	}
	else if (ast->e_type == AST_CMD)
	{
		redirects_tmp = ast->u_data.cmd.redirects;
		ret = heredoc_ast_cmd(redirects_tmp, pipefd, exc_data);
		return (ret);
	}
	return (0);
}
