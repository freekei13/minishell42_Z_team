/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:28:39 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/22 15:34:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	quotes_status(int *quote)
{
	if (*quote != 0)
		*quote = 0;
	else
		*quote = 1;
}

void	word_token(t_token **tokens, char *line, int *index, char **env, int ext_status)
{
	t_wdata	data;

	data.single_q = 0;
	data.double_q = 0;
	data.counter = *index;
	while ((line[data.counter] != ' ' && line[data.counter] != '|'
			&& line[data.counter] != '<' && line[data.counter] != '>')
			|| (data.double_q == 1 || data.single_q == 1))
	{
		if (!line[data.counter])
			break ;
		if (line[data.counter] == '\"' && data.single_q == 0)
			quotes_status(&data.double_q);
		if (line[data.counter] == '\'' && data.double_q == 0)
			quotes_status(&data.single_q);
		data.counter++;
	}
	data.word = ft_substr(line, *index, data.counter - *index);
	data.word_final = quote_sep(data.word, env, ext_status);
	if (data.word_final != NULL && (data.word_final[0] != '\0'
			|| ft_strchr(data.word, '\'') || ft_strchr(data.word, '\"')))
		add_token_back(tokens, new_token(data.word_final, WORD));
	free(data.word);
	if (data.word_final != NULL)
		free(data.word_final);
	*index = data.counter;
}
void	redirec_token(t_token **tokens, char *line, char token, int *index)
{
	if (line[*index + 1] == token)
	{
		if (token == '>')
			add_token_back(tokens, new_token(">>", APPEND));
		else if (token == '<')
			add_token_back(tokens, new_token("<<", HEREDOC));
		*index += 2;
	}
	else
	{
		if (token == '>')
			add_token_back(tokens, new_token(">", REDIRECT_OUT));
		else if (token == '<')
			add_token_back(tokens, new_token("<", REDIRECT_IN));
		*index += 1;
	}
}

t_token	*tokenize(char *line, char **env, int ext_status)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
		{
				add_token_back(&tokens, new_token("|", PIPE));
				i++;
		}
		else if (line[i] == '>')
			redirec_token(&tokens, line, '>', &i);
		else if (line[i] == '<')
			redirec_token(&tokens, line, '<', &i);
		else
			word_token(&tokens, line, &i, env, ext_status);
	}
	return (tokens);
}
