/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:53 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/13 15:25:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_bi(char **env, t_exec *exc_data)
{
	int	i;
	int		fd;

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
