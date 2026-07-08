/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 10:15:17 by marvin            #+#    #+#             */
/*   Updated: 2026/07/08 14:32:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	dash_lengh(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '/')
		i++;
	if (!str[i] || !str[i + 1])
		return (-1);
	return(i);
}

char	*no_dash(char *arg, int x)
{
	char	*str;
	int		i;

	i = -1;
	if (x != -1)
	{
		str = malloc(sizeof(char *) * (x + 1));
		while (arg[++i] && arg[i] != '/')
			str[i] = arg[i];
		str[i] = '\0';
		return(str);
	}
	else
		return(NULL);
}