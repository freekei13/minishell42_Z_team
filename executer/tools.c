/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:35:19 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/08 03:44:58 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	error_exit(int status, t_ast *ast, t_token *tokens)
{
	if (status == -1)
	{
		perror("minishell: ");
		free_tokens(tokens);
		exit (errno);
	}
}