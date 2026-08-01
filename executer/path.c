/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:13:27 by csamakka          #+#    #+#             */
/*   Updated: 2026/08/01 01:54:47 by marvin           ###   ########.fr       */
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
		cmd_path = ft_strjoin(path, ast->u_data.cmd.args[0]);
		free(path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

// PATH totalement absent de l'environnement (unset PATH) : bash cherche alors
// dans le repertoire courant, comme pour une entree vide de PATH. Renvoyer
// NULL ferait un "command not found" alors que bash lance bien la commande si
// elle est la ("unset PATH ; cd /bin ; ls" fonctionne).
char	*path_construct_cwd(t_ast *ast)
{
	char	*cmd_path;

	cmd_path = ft_strjoin("./", ast->u_data.cmd.args[0]);
	if (cmd_path && access(cmd_path, F_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*find_path(t_ast *ast, char **env)
{
	char	*path;
	char	**full_path;
	char	*cmd_path;

	path = find_env(env, "PATH");
	if (!path)
		return (path_construct_cwd(ast));
	full_path = ft_split(path, ':');
	if (!full_path)
		return (NULL);
	cmd_path = path_construct(full_path, ast);
	free_all(full_path);
	return (cmd_path);
}
