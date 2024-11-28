#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
	char* text = NULL;
	int fd;
	fd = open("tester", O_RDONLY);
	if (fd == -1)
		printf("Error reading");
	else 
		text = get_next_line(fd);
	printf("%s", text);
}

