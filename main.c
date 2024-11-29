#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
	char	*text = NULL;
	int		fd;

	fd = open("tester", O_RDONLY);
	if (fd == -1)
	{
		printf("Error reading!");
		return (1);
	}
	else
	{
		// read 1
		text = get_next_line(fd);
		printf("GNL Result: %s\n", text);
		printf("\n");
/* 		// read 2
		text = get_next_line(fd);
		printf("GNL Result: %s\n", text);
		printf("\n"); */
/* 		// read 3
		text = get_next_line(fd);
		printf("GNL Result: %s\n", text);
		printf("\n"); */
	}
	return (0);
}

