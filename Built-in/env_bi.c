/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:03:53 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/06 11:58:35 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_bi(char **env, t_exec *exc_data)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	(void) exc_data;
	return ;
}
