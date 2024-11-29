/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsarmien <dsarmien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:29 by dsarmien          #+#    #+#             */
/*   Updated: 2024/11/29 20:55:30 by dsarmien         ###   ########.fr       */
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
	
/* 	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)) //-- memory leak; */
	if (!buffer)
		buffer = ft_strdup("");
		//return (free(buffer), NULL);
	//buffer[BUFFER_SIZE] = '\0';
	// read(fd, buffer, BUFFER_SIZE) -- double read detected!;
	line = read_buffer(fd, buffer);
	//free(buffer) -- should do this?;
	printf("Pointer (to the line): %p ('%s')\n", line, line);
	return(line);
}

char* read_buffer(int fd, char*  buffer)
{
		char	*aux_ptr;
		char	*read_data;
		ssize_t	bytes_read;

		bytes_read = 1;
		while (!(ft_strchr(read_data, '\n')) && bytes_read > 0)
		{
			read_data = malloc((BUFFER_SIZE + 1) * sizeof(char));
			if (!read_data) 
				return(NULL);
			
			bytes_read = read(fd, read_data, BUFFER_SIZE);
			printf("Bytes read: %lu\n", bytes_read);
			printf("Static Buffer (before initialize): %s\n", buffer);

			aux_ptr = buffer;
			// printf("Old memaddr: %p\n", buffer);
			if (bytes_read != 0)
			{
				buffer = ft_strjoin(buffer, read_data);
			}
			else
				break;
			// printf("New memaddr: %p\n", buffer);
			// printf("Ptr memaddr: %p\n", aux_ptr);

			printf("Static Buffer (after initialize): %s\n", buffer);
			free(read_data);
			read_data = NULL;
			free(aux_ptr);
		}
		return(buffer);
}
