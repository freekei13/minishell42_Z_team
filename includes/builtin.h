/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:58:05 by lalamino          #+#    #+#             */
/*   Updated: 2026/05/13 11:47:51 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

void	env_bi(char **env);
void	pwd(char **env);
char	**unset(char **env, t_ast cmd);
char	**export(char **env, t_ast cmd);
void	echo_fct(char	**str, int option);
int		args_size(char **args);
int		cd(char **args, char **env);


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