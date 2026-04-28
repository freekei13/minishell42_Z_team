/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:58:05 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/21 14:07:09 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "executing.h"
# include "lexing.h"
# include "parsing.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

void	env(char **env);
void	pwd(char **env);
char	**unset(char **env, t_ast cmd);
char	**export(char **env, t_ast cmd);
void	echo_fct(t_ast cmd);
int		args_size(char **args);


typedef struct s_int
{
	int	i;
	int	is;
	int	j;
	int	js;
	int	k;
	int	ks;

}	t_int;

#endif