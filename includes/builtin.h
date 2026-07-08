/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:58:05 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/07 16:51:16 by marvin           ###   ########.fr       */
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
int		builtin(t_ast *cmd, char ***env, t_exec *exc_data);
void	env_bi(char **env, t_exec *exc_data);
void	pwd(char **env, t_exec *exc_data);
void	unset(char ***env, char **cmd, t_exec *exc_data);
void	export(char ***env, char **cmd, t_exec *exc_data);
void	echo_fct(char	**str, int option, t_exec *exc_data);
int		args_size(char **args);
void	cd(char **args, char **env, t_exec *exc_data);
void	exit_fct(t_ast *ast, char ***env, t_exec *exc_data);

#endif