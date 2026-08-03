/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 10:15:17 by marvin            #+#    #+#             */
/*   Updated: 2026/08/03 13:21:31 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"


int	is_valid_id(char *s)
{
	int	i;

	if (!s || !s[0])
		return (1);
	if (s[0] == '-')
		return (2);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (1);
	i = 0;
	while (s[++i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (1);
	}
	return (0);
}

void	option_error(char *bi, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(bi, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": invalid option", 2);
}

void	id_error(char *bi, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(bi, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
