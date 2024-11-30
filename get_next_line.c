/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsarmien <dsarmien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:29 by dsarmien          #+#    #+#             */
/*   Updated: 2024/11/30 18:55:52 by dsarmien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char*	read_buffer(int fd, char *buffer);

char	*get_next_line(int fd)
{
	char	*line;
	static char	*buffer;
	
	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FD)
		return (NULL);
	
/* 	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)) //-- memory leak; */
	if (!buffer)
	{
		buffer = ft_strdup("");
		//return (free(buffer), NULL);
	}
	//buffer[BUFFER_SIZE] = '\0';
	// read(fd, buffer, BUFFER_SIZE) -- double read detected!;
	//line = read_buffer(fd, buffer);
	line = get_one_line(buffer);
	//free(buffer) -- should do this?;
	//printf("Line Pointer: %p -> %s\n", line, line);
	buffer = NULL;
	return(line);
}

char	*read_buffer(int fd, char *buffer)
{
		char	*aux_ptr;
		char	*read_data;
		ssize_t	bytes_read;
		size_t	count;

		bytes_read = 1;
		count = 0;
		while (!(ft_strchr(read_data, '\n')) && bytes_read > 0)
		{
			read_data = malloc((BUFFER_SIZE + 1) * sizeof(char));
			if (!read_data) 
				return(NULL);
			
			bytes_read = read(fd, read_data, BUFFER_SIZE);
			printf("\nBytes read: %lu | Iteration (read): %zu\n", bytes_read, count + 1);
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
			count++;
		}
		return(buffer);
}
