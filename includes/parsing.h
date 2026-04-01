/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:36:15 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/01 21:45:29 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

typedef struct s_ast
{
	enum
	{
		AST_CMD,
		AST_PIPE
	}	type;
	union
	{
		t_cmd	cmd;
		t_pipe	pipe;
	}	data;
	
}	t_ast;

t_redirect	*new_redirect(char *value, int type);
void		add_redirect_back(t_redirect **lst, t_redirect *new);
void		free_redirects(t_redirect *lst);

#endif