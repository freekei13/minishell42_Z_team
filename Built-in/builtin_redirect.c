/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 11:55:01 by lalamino          #+#    #+#             */
/*   Updated: 2026/06/24 18:29:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

redirect_bi1(t_ast *cmd, char ***env, int i, int nberr)
{
	ft_strnc
	if (i == 7)
		printf("not a builtin command");
	else if (i >= 8)
	{
		
	}
	else if (i == 0)
	{
		
	}
	else if (i >= 1)
		redirect_bi2(cmd, env, i, nberr);
}

redirect_bi2(t_ast *cmd, char ***env, int i, int nberr)
{
	if (i == 1)
	{

	}
	else if (i == 2)
	{

	}
	else if (i == 3)
	{
		
	}
	else if (i >= 4)
		redirect_bi3(cmd, env, i, nberr);
}

redirect_bi3(t_ast *cmd, char ***env, int i, int nberr)
{
	if (i == 4)
	{
		
	}
	else if (i == 5)
	{
		
	}
	else if (i == 6)
	{
		
	}
}
