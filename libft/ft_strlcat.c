/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freekei <freekei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:41 by csamakka          #+#    #+#             */
/*   Updated: 2025/11/13 15:13:06 by freekei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		dest_len = size;
	if (dest_len == size)
		return (dest_len + src_len);
	if (src_len < size - dest_len)
	{
		ft_memcpy(dest + dest_len, src, src_len + 1);
	}
	else
	{
		ft_memcpy(dest + dest_len, src, size - dest_len - 1);
		dest[size - 1] = 0;
	}
	return (dest_len + src_len);
}
