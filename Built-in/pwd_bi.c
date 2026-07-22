/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:15 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/23 00:48:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	pwd(char **env, t_exec *exc_data)
{
	int	fd;
	
	exc_data->data->exit_status = 0;
	if (exc_data->fd_out == -1)
		fd = 1;
	else
		fd = exc_data->fd_out;
	ft_putendl_fd(find_env(env, "PWD"), fd);
}

