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

void init_map(t_game *game)
{
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';
}

void clean_config(t_game *game)
{
	free(game->config.no_text);
	free(game->config.so_text);
	free(game->config.ea_text);
	free(game->config.we_text);
}

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

int	main(int ac, char **av)
{
	t_game game;


	if (ac != 2)
		return (print_error("Invalid number of args"), 1);
	if (parse_file(&game, av[1]))
		return (1);
	init_config(&game);
	init_map(&game);
	extract_data(&game);
	if (!validate_config(&game))
	{
		clean_config(&game);
		close(game.fd);
		return 1;
	}
	validate_map(&game.map);
	for (int i = 0; game.map.grid[i]; i++)
		free(game.map.grid[i]);
	free(game.map.grid);
	clean_config(&game);
	close(game.fd);
	return 0;
}
