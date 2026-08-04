/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:28:39 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/04 14:20:10 by marvin           ###   ########.fr       */
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

void	word_end(t_cursor *cur, t_wdata *data)
{
	while ((!is_blank(cur->line[data->counter])
			&& cur->line[data->counter] != '|'
			&& cur->line[data->counter] != '<'
			&& cur->line[data->counter] != '>')
		|| (data->double_q == 1 || data->single_q == 1))
	{
		if (!(cur->line[data->counter]))
			break ;
		if (cur->line[data->counter] == '\"' && data->single_q == 0)
			quotes_status(&data->double_q);
		if (cur->line[data->counter] == '\'' && data->double_q == 0)
			quotes_status(&data->single_q);
		data->counter++;
	}
}

void	word_token(t_token **tokens, t_cursor *cur, char **env, int ext_status)
{
	t_wdata	data;

	data.single_q = 0;
	data.double_q = 0;
	data.counter = cur->index;
	word_end(cur, &data);
	data.word = ft_substr(cur->line, cur->index, data.counter - cur->index);
	if (cur->hd_delim == 1)
		data.word_final = heredoc_delim(data.word);
	else
		data.word_final = quote_sep(data.word, env, ext_status);
	if (data.word_final != NULL && (data.word_final[0] != '\0'
			|| ft_strchr(data.word, '\'') || ft_strchr(data.word, '\"')))
		add_word_tokens(tokens, data.word_final);
	if (cur->hd_delim == 1)
		mark_hd_delim(*tokens, data.word);
	cur->hd_delim = 0;
	free(data.word);
	if (data.word_final != NULL)
		free(data.word_final);
	cur->index = data.counter;
}

void	redirec_token(t_token **tokens, char token, t_cursor *cur)
{
	if (cur->line[cur->index + 1] == token)
	{
		if (token == '>')
			add_token_back(tokens, new_token(">>", APPEND));
		else if (token == '<')
		{
			add_token_back(tokens, new_token("<<", HEREDOC));
			cur->hd_delim = 1;
		}
		cur->index += 2;
	}
	else
	{
		if (token == '>')
			add_token_back(tokens, new_token(">", REDIRECT_OUT));
		else if (token == '<')
			add_token_back(tokens, new_token("<", REDIRECT_IN));
		cur->index += 1;
	}
}

t_token	*tokenize(char *line, char **env, int ext_status)
{
	t_token		*tokens;
	t_cursor	cur;

	tokens = NULL;
	cur.line = line;
	cur.index = 0;
	cur.hd_delim = 0;
	while (line[cur.index])
	{
		if (is_blank(line[cur.index]))
			cur.index++;
		else if (line[cur.index] == '|')
		{
			add_token_back(&tokens, new_token("|", PIPE));
			cur.index++;
		}
		else if (line[cur.index] == '>')
			redirec_token(&tokens, '>', &cur);
		else if (line[cur.index] == '<')
			redirec_token(&tokens, '<', &cur);
		else
			word_token(&tokens, &cur, env, ext_status);
	}
	return (tokens);
}
