/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsarmien <dsarmien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:29 by dsarmien          #+#    #+#             */
/*   Updated: 2024/11/28 21:01:45 by dsarmien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char* read_buffer(int fd, char*  buffer);

char	*get_next_line(int fd)
{
	char* line;
	static char* buffer;
	
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FD)
		return (NULL);
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(buffer), NULL);
	buffer[BUFFER_SIZE] = '\0';
	read(fd, buffer, BUFFER_SIZE);
	line = read_buffer(fd, buffer);
	printf("Pointer: %p\nContent: %s\n", line, line);
	return(line);
}

char* read_buffer(int fd, char*  buffer)
{
		char* tmp;
		ssize_t bytes_read;
		tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp) 
			return(NULL);

		bytes_read = read(fd, tmp, BUFFER_SIZE);
		printf("Bytes read: %lu \nTemporary buffer: %s\n", bytes_read, tmp);
		buffer = ft_strjoin(buffer, tmp);
		printf("Static buffer: %s\n", buffer);
		free(tmp);
		return(buffer);
}
