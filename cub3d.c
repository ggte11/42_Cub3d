#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game game;


	if (ac != 2)
		return (print_error("Invalid number of args"), 1);
	if (parse_file(&game, av[1]))
		return (1);
	printf("Success\n");
	close(game.fd);
	return 0;
}
