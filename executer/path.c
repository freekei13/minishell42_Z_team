/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:13:27 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/11 16:44:11 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	*find_path(t_ast *ast, char **env)
{
	int		i;
	int		j;
	char	**full_path;
	char	*cmd_path;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			full_path = ft_split(env[i], ':');
			j = 0;
			while (full_path[j])
			{
				path = ft_strjoin(full_path[j], "/");
				cmd_path = ft_strjoin(path, ast->data.cmd.args[0]);
				free(path);
				if (access(cmd_path, F_OK) == 0)
					return (free_all(full_path), cmd_path);
				free(cmd_path);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}