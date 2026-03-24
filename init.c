#include "cub3d.h"

void init_config(t_game *game)
{
	game->texture.path[NO] = NULL;
	game->texture.path[SO] = NULL;
	game->texture.path[WE] = NULL;
	game->texture.path[EA] = NULL;
	game->texture.floor_color = -1;
	game->texture.ceiling_color = -1;
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
