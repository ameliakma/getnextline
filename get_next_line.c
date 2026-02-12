/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalfou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:39:37 by akhalfou          #+#    #+#             */
/*   Updated: 2026/02/12 21:26:58 by akhalfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*read_and_join(int fd, char *buffer, char *buf)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (bytes_read == 0)
		return (buffer);
	buf[bytes_read] = '\0';
	tmp = ft_strjoin(buffer, buf);
	free(buffer);
	return (tmp);
}

char	*read_stash(int fd, char *buffer)
{
	char	*buf;
	char	*tmp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(buffer);
		return (NULL);
	}
	while (!ft_strchr(buffer, '\n'))
	{
		tmp = read_and_join(fd, buffer, buf);
		if (!tmp)
			return (free(buf), NULL);
		if (tmp == buffer)
			break ;
		buffer = tmp;
	}
	free(buf);
	return (buffer);
}

char	*extract_line(char *buffer)
{
	char	*str;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		str = ft_substr(buffer, 0, i + 1);
	else
		str = ft_substr(buffer, 0, i);
	return (str);
}

char	*new_str(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	str = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = read_stash(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	buffer = new_str(buffer);
	return (line);
}
