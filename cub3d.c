#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (print_error("Invalid number of params"), 1); // mudar
	parse_file(av[1]);
	init_game(&game);
	mlx_loop(game.mlx);
}