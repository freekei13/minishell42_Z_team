/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:58:05 by lalamino          #+#    #+#             */
/*   Updated: 2026/06/22 13:36:38 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parsing.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_int
{
	int	i;
	int	is;
	int	j;
	int	js;
	int	k;
	int	ks;

}	t_int;

int		dash_lengh(char *str);
int		builtin(t_ast *cmd, char ***env);
void	env_bi(char **env);
void	pwd(char **env);
void	unset(char ***env, char **cmd);
void	export(char ***env, char **cmd);
void	echo_fct(char	**str, int option);
int		args_size(char **args);
int		cd(char **args, char **env);

#endif