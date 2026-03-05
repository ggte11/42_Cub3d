#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (print_error("Invalid number of params"), 1); // mudar
	parse_file(av[1]);
	init_game(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_realease, &game.player);
	draw_square(game.player.x, game.player.y, 64, 0x00FF00, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}
