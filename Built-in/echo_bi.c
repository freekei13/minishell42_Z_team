/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:02:45 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/13 15:25:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	echo_fct(char **str, int option, t_exec *exc_data)
{
	t_int	i;
	int		fd;

	exc_data->data->exit_status = 0;
	if (exc_data->fd_out == -1)
		fd = 1;
	else
		fd = exc_data->fd_out;
	if (!str)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	i.i = -1;
	exc_data->data->exit_status = 0;
	while (str[++i.i] && str[i.i] != NULL)
	{
		ft_putstr_fd(str[i.i], fd);
		if (str[i.i + 1])
			ft_putstr_fd(" ", fd);
	}
	if (option == 0 && !str[i.i])
		ft_putstr_fd("\n", fd);
}
	