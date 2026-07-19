/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:48 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/19 03:13:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	unset(char ***env, char **cmd, t_exec *exc_data)
{
	char	*tab[2];
	int		i;

	exc_data->data->exit_status = 0;
	i = -1;
	while (cmd[++i])
	{
		if (!is_valid_id(cmd[i]) || ft_strchr(cmd[i], '=') != NULL)
		{
			id_error("unset", cmd[i]);
			exc_data->data->exit_status = 1;
		}
		else if (find_env(*env, cmd[i]) != NULL)
		{
			tab[0] = cmd[i];
			tab[1] = NULL;
			*env = rmv_env(*env, tab);
		}
	}
}

// char	**mlc_init(char **cmd)
// {
// 	char	**mlc;
// 	int		i;

// 	i = 0;
// 	while (cmd[i])
// 		i++;
// 	mlc = malloc(sizeof(char *) * (i + 1));
// 	return (mlc);
// }

// void	unset(char ***env, char **cmd, t_exec *exc_data)
// {
// 	char	**valid_args;
// 	int		i;
// 	int		s;

// 	exc_data->data->exit_status = 0;
// 	i = 0;
// 	valid_args = mlc_init(cmd);
// 	i = -1;
// 	s = -1;
// 	while (cmd[++i] != NULL)
// 	{
// 		if (find_env(*env, cmd[i]) != NULL)
// 			valid_args[++s] = ft_strdup(cmd[i]);
// 	}
// 	valid_args[++s] = NULL;
// 	if (s > 0)
// 		*env = rmv_env(*env, valid_args);
// 	else
// 	{
// 		split_free(valid_args);
// 		printf("unset - arguments non valides\n");
// 		return ;
// 	}
// 	split_free(valid_args);
// 	return ;
// }
