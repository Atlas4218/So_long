#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int	fd;
	char	*line;

	line = "";
	if (ac != 2)
		return (write(1, "Ajouter seulement 1 nom de fichier en argument", 50));
	fd = open(av[1], O_RDONLY);
	while(line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
}
	

