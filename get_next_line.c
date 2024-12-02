/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsarmien <dsarmien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:29:32 by dsarmien          #+#    #+#             */
/*   Updated: 2024/12/02 18:36:27 by dsarmien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_fd(int fd, char *buffer)
{
	char	*ptr;
	char	*data;
	ssize_t	bytes;

	bytes = 1;
	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while ((!buffer) || (!ft_strchr(buffer, '\n') && bytes > 0))
	{
		bytes = read(fd, ptr, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_memclean(ptr));
		ptr[bytes] = '\0'; // we need this?
		data = buffer;
		buffer = ft_strjoin(buffer, ptr);
		free(data);
		ft_memclean(ptr);
	}
	// free(ptr);
	return (buffer);
}

char	*ft_get_line(char *str)
{
	char	*next_line;
	char	*n_pos;
	char	*aux;
	size_t	i;

	if (!*str)
		return (NULL);
	n_pos = ft_strchr(str, '\n');
	if (n_pos)
		i = n_pos - str + 1;
	else
		i = ft_strlen(str);
	next_line = malloc((i + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	ft_memcpy(next_line, str, i);
	next_line[i] = '\0';
	aux = str;
	str = n_pos;
	ft_memclean(aux);
 	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp_buffer;
	char		*line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1 * sizeof(char));
		if (!buffer)
			return(free(buffer), NULL);
		buffer[0] = '\0';//??????
	}
	buffer = ft_read_fd(fd, buffer);
	//printf("Buffer Pointer: %p -> %s\n", buffer, buffer);
	tmp_buffer = buffer; // forgot to free
	line = ft_get_line(buffer);
	//printf("Line Pointer: %p -> %s\n", line, line);
	/*
		WORKING HERE / ToDo
		
		-> We need to update the buffer
	*/
	ft_update_buffer(line);
	return (line);
}
