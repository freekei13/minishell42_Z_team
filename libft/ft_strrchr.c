/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:11:18 by csamakka          #+#    #+#             */
/*   Updated: 2025/10/03 16:13:19 by csamakka         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*str;
	unsigned char		ch;
	const unsigned char	*last_found;

	str = (const unsigned char *)s;
	ch = (unsigned char)c;
	last_found = NULL;
	while (*str)
	{
		if (*str == ch)
			last_found = str;
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return ((char *)last_found);
}
