/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:02:45 by lalamino          #+#    #+#             */
/*   Updated: 2026/04/28 14:11:41 by lalamino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	whole_size(char **str)
{
	int	i;
	int	j;
	int	res;
	
	res = 0;
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j])
			j++;
		res += j;
	}
	res += i;
	return (res);
}

int	count_files(t_ast cmd)
{
	t_int	i;

	i.i = -1;
	i.k = 0;
	while(cmd.data.cmd.args[++i.i])
	{
		i.is = -1;
		while (cmd.data.cmd.args[i.i][++i.is])
		{
			if (cmd.data.cmd.args[i.i][i.is] == '>')
				i.k++;
		}
	}
	return (i.k);
}

void	echo_fct(t_ast cmd)
{
	char	*str;
	char	**file;
	t_int	i;

	i.k = -1;
	i.i = -1;
	i.j = -1;
	file = NULL;
	file = malloc(sizeof(char **) * (count_files(cmd) + 1));
	str = malloc(sizeof(char *) * (whole_size(cmd.data.cmd.args) + 1));
	while (cmd.data.cmd.args[++i.i])
	{
		i.is = 0;
		while (cmd.data.cmd.args[i.i][++i.is]
				&& cmd.data.cmd.args[i.i][i.is] != '>')
			str[++i.j] = cmd.data.cmd.args[i.i][i.is];
		if (cmd.data.cmd.args[i.i][i.is] == '>')
		{
			file[++i.k] = ft_substr(cmd.data.cmd.args[i.i], i.is + 1,
				ft_strlen(cmd.data.cmd.args[i.i]) - i.is);
		}
	}
	printf("%s\n", str);
	int l;
	l = -1;
	while (file[++l])
		printf("\n%s\n", file[l]);
}
//not done