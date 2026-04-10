/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:32:58 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/08 12:38:07 by lalamino         ###   ########.fr       */
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

typedef enum e_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
}	t_type;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

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