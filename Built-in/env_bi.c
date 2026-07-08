/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:53 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/08 14:35:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_bi(char **env, t_exec *exc_data)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	exc_data->data->exit_status = 0;
	return ;
}
