#include "cub3d.h"

void init_config(t_game *game)
{
	game->config.no_text = NULL;
	game->config.so_text = NULL;
	game->config.ea_text = NULL;
	game->config.we_text = NULL;
	game->config.floor_color = -1;
	game->config.ceiling_color = -1;
}

int	main(int ac, char **av)
{
	t_game game;


	if (ac != 2)
		return (print_error("Invalid number of args"), 1);
	if (parse_file(&game, av[1]))
		return (1);
	init_config(&game);
	extract_data(&game);
	puts(game.config.no_text);
	puts(game.config.so_text);
	puts(game.config.ea_text);
	puts(game.config.we_text);
	printf("%X\n", game.config.floor_color);
	printf("%X\n", game.config.ceiling_color);
	close(game.fd);
	return 0;
}
