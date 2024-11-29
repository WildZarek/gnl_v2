/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsarmien <dsarmien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:29 by dsarmien          #+#    #+#             */
/*   Updated: 2024/11/29 16:55:52 by dsarmien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char*	read_buffer(int fd, char*  buffer);

char	*get_next_line(int fd)
{
	char	*line;
	static char	*buffer;
	
	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FD)
		return (NULL);
	
	//buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)) -- memory leak;
	if (!buffer)
		return (free(buffer), NULL);
	buffer[BUFFER_SIZE] = '\0';
	// read(fd, buffer, BUFFER_SIZE) -- double read detected!;
	line = read_buffer(fd, buffer);
	//free(buffer) -- should do this?;
	printf("Pointer (to the line): %p ('%s')\n", line, line);
	return(line);
}

char* read_buffer(int fd, char*  buffer)
{
		char	*ptr;
		char	*tmp;
		ssize_t	bytes_read;
		tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp) 
			return(NULL);

		bytes_read = read(fd, tmp, BUFFER_SIZE);
		printf("Bytes read: %lu\n", bytes_read);
		printf("Static Buffer (before initialize): %s\n", buffer);
		if (!buffer)
			buffer = tmp;
		else
		{
			ptr = ft_strjoin(buffer, tmp);
			free(ptr);
			tmp = NULL;
			if (!ptr)
				return (NULL);
		}
		printf("Static Buffer (after initialize): %s\n", buffer);
		free(tmp);
		return(buffer);
}
