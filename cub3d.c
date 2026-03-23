#include "cub3d.h"

int check_config(t_game *game)
{
	if (!game->config.no_text)
		return (0);
	if (!game->config.so_text)
		return (0);
	if (!game->config.ea_text)
		return (0);
	if (!game->config.we_text)
		return (0);
	if (game->config.floor_color == -1)
		return (0);
	if (game->config.ceiling_color == -1)
		return (0);
	return (1);
}

int validate_config(t_game *game)
{
	if (!check_config(game))
		return (print_error(FORM_ERR), 0);
	return (1);
}

int	on_destroy(t_game *game)
{
	clean_map(game->map.grid);
	clean_config(game);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (print_error("Invalid number of args"), 1);
	init_config(&game);
	init_map(&game);
	if (parse_file(&game, av[1]))
		return (1);
	extract_data(&game);
	if (!validate_config(&game) || !validate_map(&game.map))
		return (clean_map(game.map.grid), clean_config(&game), 1);
	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_realease, &game.player);
	mlx_hook(game.win, 17, 1L << 17, (int (*)())on_destroy, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	clean_map(game.map.grid);
	clean_config(&game);
	return 0;
}
