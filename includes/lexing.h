/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:32:58 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/07 18:00:58 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

extern int g_status;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	AND,
	OR
}	t_type;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_wdata
{
	int		counter;
	int		single_q;
	int		double_q;
	char	*word;
	char	*word_final;
}	t_wdata;

typedef struct s_dquote
{
	char	*money;
	char	quote;
	int		q_val;
	char	*res;
	char	**split;
	char	*temp;
	char	*save;
	int		i;
	int		j;
	int		s;
}	t_dquote;

t_token	*new_token(char *value, int type);
void	add_token_back(t_token **lst, t_token *new);
void	free_tokens(t_token *lst);
int		quote_check(char *str);
char	*quote_sep(char *str, char **env);
char	**make_env(char **env);
char	*find_env(char **env, char *cherche);
char	**dequote(t_dquote qt, char *str, char **env);
void	split_free(char **split);

t_token	*tokenize(char *line, char **env);
#endif