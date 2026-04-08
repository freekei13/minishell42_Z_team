/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:28:39 by csamakka          #+#    #+#             */
/*   Updated: 2026/03/31 14:46:39 by lalamino         ###   ########.fr       */
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

void	word_token(t_token **tokens, char *line, int *index)
{
	int		counter;
	int		single_q;
	int		double_q;
	char	*word;

	single_q = 0;
	double_q = 0;
	counter = *index;
	while ((line[counter] != ' ' && line[counter] != '|'
			&& line[counter] != '<' && line[counter] != '>')
			|| (double_q == 1 || single_q == 1))
	{
		if (!line[counter])
			break ;
		if (line[counter] == '\"' && single_q == 0)
			quotes_status(&double_q);
		if (line[counter] == '\'' && double_q == 0)
			quotes_status(&single_q);
		counter++;
	}
	word = ft_substr(line, *index, counter - *index);
	quote_sep(word);
	add_token_back(tokens, new_token(word, WORD));
	free(word);
	*index = counter;
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

t_token	*tokenize(char *line)
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
			word_token(&tokens, line, &i);
	}
	return (tokens);
}
