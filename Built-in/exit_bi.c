/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:44 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/06 11:58:40 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	exit_fct(t_ast *ast, char **env, t_exec *exc_data)
{
	
	free_ast(ast);
	split_free(env);
	(void) exc_data;
	exit(0) ;
}