/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:53 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/30 21:26:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// export NAME+=valeur : bash concatene a la valeur existante au lieu de la
// remplacer. A partir de "NAME+=valeur" (len = index du '='), renvoie une
// entree "NAME=ancienne_valeurvaleur" fraichement allouee. Variable absente
// -> ancienne valeur vide, donc equivalent a un export simple.
char	*append_arg(char **env, char *arg, int len)
{
	char	*name;
	char	*old;
	char	*tmp;
	char	*res;

	name = ft_substr(arg, 0, len - 1);
	if (!name)
		return (NULL);
	old = find_env(env, name);
	if (!old)
		old = "";
	tmp = ft_strjoin(name, "=");
	free(name);
	if (!tmp)
		return (NULL);
	name = ft_strjoin(tmp, old);
	free(tmp);
	if (!name)
		return (NULL);
	res = ft_strjoin(name, arg + len + 1);
	free(name);
	return (res);
}

// bash n'affiche jamais "_" dans la sortie de "export" : c'est une variable
// que le shell gere lui-meme et place directement dans l'environnement des
// commandes lancees, sans l'attribut export. Elle reste visible dans "env".
void	print_export_line(char *entry, int j)
{
	ft_putstr_fd("declare -x ", 1);
	if (!entry[j])
		ft_putendl_fd(entry, 1);
	else
	{
		write(1, entry, j + 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(entry + j + 1, 1);
		ft_putendl_fd("\"", 1);
	}
}

// Copie de l'environnement au demarrage + increment de SHLVL, comme le fait
// bash a chaque nouveau shell. Sans ca "export" affiche SHLVL="1" la ou bash
// affiche "2". Valeur absente ou non numerique -> 1, comme bash.
char	**env_setup(char **envi)
{
	char	**env;
	char	*old;
	char	*nb;
	char	*line;

	env = make_env(envi);
	old = find_env(env, "SHLVL");
	if (old && ft_isdigit(old[0]))
		nb = ft_itoa(ft_atoi(old) + 1);
	else
		nb = ft_itoa(1);
	if (!nb)
		return (env);
	line = ft_strjoin("SHLVL=", nb);
	free(nb);
	if (!line)
		return (env);
	export_one(&env, line);
	free(line);
	return (env);
}

void	env_bi(char **env, t_exec *exc_data)
{
	int	i;
	int	fd;

	exc_data->data->exit_status = 0;
	if (exc_data->fd_out == -1)
		fd = 1;
	else
		fd = exc_data->fd_out;
	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], fd);
		ft_putstr_fd("\n", fd);
	}
	return ;
}
