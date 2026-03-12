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
	game->map.grid = NULL;
	game->map.m_width = 0;
	game->map.m_height = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';
}