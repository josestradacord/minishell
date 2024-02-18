/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:14:58 by joestrad          #+#    #+#             */
/*   Updated: 2023/12/01 19:50:40 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_new_buffer(char *buff1, char *buff2)
{
	char	*buff;

	buff = ft_strjoin(buff1, buff2);
	free(buff1);
	return (buff);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	int		index;

	index = 0;
	if (!buffer[index])
		return (NULL);
	while (buffer[index] && buffer[index] != '\n')
		index++;
	line = (char *) ft_calloc(index + 2, sizeof(char));
	if (!line)
		return (NULL);
	index = 0;
	while (buffer[index] && buffer[index] != '\n')
	{
		line[index] = buffer[index];
		index++;
	}
	if (buffer[index] && buffer[index] == '\n')
		line[index] = '\n';
	return (line);
}

static char	*ft_read_from_file(int fd, char *str)
{
	char	*buffer;
	ssize_t	bytes_readed;

	buffer = (char *) ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_readed = 1;
	while (bytes_readed > 0)
	{
		bytes_readed = read (fd, buffer, BUFFER_SIZE);
		if (bytes_readed == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_readed] = '\0';
		str = ft_new_buffer(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

static char	*ft_update_buffer(char *buffer)
{
	int		index1;
	int		index2;
	char	*res;

	index1 = 0;
	while (buffer[index1] && buffer[index1] != '\n')
		index1++;
	if (!buffer[index1])
	{
		free(buffer);
		return (NULL);
	}
	res = (char *) ft_calloc((ft_strlen(buffer) - index1 + 1), sizeof(char));
	if (!res)
		return (NULL);
	index1++;
	index2 = 0;
	while (buffer[index1])
		res[index2++] = buffer[index1++];
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;

	if (!buffer)
		buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	res = ft_get_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (res);
}
