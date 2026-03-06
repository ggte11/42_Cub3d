#include "../cub3d.h"

bool	touch_wall(float px, float py, t_game *game)
{
	int	x = px / BLOCK;
	int y = py / BLOCK;

	if (game->map.grid[y][x] == '1')
		return (true);
	return (false);
}