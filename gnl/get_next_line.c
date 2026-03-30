/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:42:59 by csamakka          #+#    #+#             */
/*   Updated: 2025/10/29 14:17:13 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_all_line(int fd, char *buffer, char *left_line);
char	*fill_line(char *left_line);
char	*fill_left_line(char *left_line);

char	*get_next_line(int fd)
{
	static char	*left_line;
	char		*buffer;
	char		*line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE < 0)
	{
		free(buffer);
		buffer = NULL;
		free(left_line);
		left_line = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	left_line = fill_all_line(fd, buffer, left_line);
	free(buffer);
	buffer = NULL;
	if (!left_line)
		return (NULL);
	line = fill_line(left_line);
	if (left_line)
		left_line = fill_left_line(left_line);
	return (line);
}

char	*fill_all_line(int fd, char *buffer, char *left_line)
{
	char	*tmp;
	ssize_t	bytes;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(left_line);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		if (!left_line)
			left_line = ft_strdup("");
		buffer[bytes] = 0;
		tmp = left_line;
		left_line = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(left_line, '\n'))
			break ;
	}
	return (left_line);
}

char	*fill_line(char *left_line)
{
	char	*line;
	int		i;

	i = 0;
	if (!left_line[i])
		return (NULL);
	while (left_line[i] != '\n' && left_line[i] != '\0')
		i++;
	if (left_line[i] == '\n')
		line = ft_substr(left_line, 0, i + 1);
	else
	{
		line = ft_substr(left_line, 0, i);
	}
	return (line);
}

char	*fill_left_line(char *left_line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (left_line[i] != '\n' && left_line[i] != '\0')
		i++;
	if (!left_line[i])
		return (free(left_line), NULL);
	tmp = left_line;
	left_line = ft_substr(left_line, i + 1, ft_strlen(tmp) - (i + 1));
	free(tmp);
	tmp = NULL;
	return (left_line);
}
