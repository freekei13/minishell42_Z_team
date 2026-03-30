/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:55:26 by csamakka          #+#    #+#             */
/*   Updated: 2025/10/09 14:07:25 by csamakka         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	set_counter(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim_str;
	size_t	s1_len;

	start = 0;
	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	end = ft_strlen(s1);
	s1_len = ft_strlen(s1);
	while (s1[start] && set_counter(s1[start], set))
		start++;
	while (s1[end - 1] && set_counter(s1[end - 1], set) && end > start)
		end--;
	trim_str = ft_substr(s1, start, s1_len - start - (s1_len - end));
	return (trim_str);
}
