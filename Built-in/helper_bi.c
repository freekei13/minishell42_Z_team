/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 10:15:17 by marvin            #+#    #+#             */
/*   Updated: 2026/07/29 20:38:28 by marvin           ###   ########.fr       */
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
	return (i);
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
		return (str);
	}
	else
		return (NULL);
}

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
