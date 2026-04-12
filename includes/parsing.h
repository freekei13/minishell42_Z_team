/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:36:15 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/12 13:36:01 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PIPE_UNEXPECTED "minishell: syntax error near unexpected token `|'\n"
# include "lexing.h"

typedef struct s_ast t_ast;

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char				**args;
	struct s_redirect	*redirects;
}	t_cmd;

typedef struct s_pipe
{
	struct s_ast	*left;
	struct s_ast	*right;
}	t_pipe;

typedef struct	s_error
{
	int		status_code;
	char	*err_message;
}	t_error;

typedef struct s_ast
{
	enum
	{
		AST_CMD,
		AST_PIPE,
		AST_ERROR
	}	type;
	union
	{
		t_cmd	cmd;
		t_pipe	pipe;
		t_error	err;
	}	data;
	
}	t_ast;

t_redirect	*new_redirect(char *value, int type);
void		add_redirect_back(t_redirect **lst, t_redirect *new);
void		free_redirects(t_redirect *lst);

t_ast		*parser(t_token *tokens);

void		print_ast(t_ast *ast, int level);
#endif