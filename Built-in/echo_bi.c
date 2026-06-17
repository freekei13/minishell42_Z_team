/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:02:45 by lalamino          #+#    #+#             */
/*   Updated: 2026/06/17 21:32:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	echo_fct(char	**str, int option)
{
	t_int	i;
	
	i.i = -1;
	while (str[++i.i] && str[i.i] != NULL)
	{
		printf("%s", str[i.i]);
		if (str[i.i + 1])
			printf(" ");
	}
	if (option == 0 && !str[i.i])
		printf("\n");
}
	