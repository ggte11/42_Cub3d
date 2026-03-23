#include "../cub3d.h"

bool	touch_wall(float px, float py, t_game *game)
{
	int		x;
	int		y;
	int		row_len;
	char	cell;

	if (px < 0 || py < 0)
		return (true);
	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (y < 0 || y >= game->map.m_height || !game->map.grid[y])
		return (true);
	row_len = ft_strlen(game->map.grid[y]);
	if (x < 0 || x >= row_len)
		return (true);
	cell = game->map.grid[y][x];
	if (cell == '1' || cell == ' ')
		return (true);
	return (false);
}
