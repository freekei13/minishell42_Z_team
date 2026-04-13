/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:13:27 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/13 15:27:59 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	*path_construct(char **full_path, t_ast *ast)
{
	char	*cmd_path;
	char	*path;
	int		i;
	
	i = 0;
	while (full_path[i])
	{
		path = ft_strjoin(full_path[i], "/");
		cmd_path = ft_strjoin(path, ast->data.cmd.args[0]);
		free(path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*find_path(t_ast *ast, char **env)
{
	int		i;
	char	**full_path;
	char	*cmd_path;
	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			full_path = ft_split(env[i], ':');
			cmd_path = path_construct(full_path, ast);
			if (!cmd_path)
			{
				free_all(full_path);
				break ;
			}
			free_all(full_path);
		}
		i++;
	}
	return (cmd_path);
}
