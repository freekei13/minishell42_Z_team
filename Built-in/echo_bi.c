/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:02:45 by lalamino          #+#    #+#             */
/*   Updated: 2026/07/06 11:58:13 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	echo_fct(char	**str, int option, t_exec *exc_data)
{
	t_int	i;
	
	i.i = -1;
	while (str[++i.i] && str[i.i] != NULL)
	{
		printf("%s", str[i.i]);
		if (str[i.i + 1])
			printf(" ");
	}
	(void) exc_data;
	if (option == 0 && !str[i.i])
		printf("\n");
}
	