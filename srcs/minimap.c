#include "../cub3d.h"

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;
	int	px;
	int	py;

	size = (int)(TILE * MINIMAP_SCALE);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			px = MINIMAP_X + (x * size) + i;
			py = MINIMAP_Y + (y * size) + i;
			put_pixel(px, py, color, game);
			j++;
		}
		i++;
	}
}

static void	draw_player_minimap(t_game *game)
{
	int	size;
	int	px;
	int	py;
	int	i;
	int	j;

	size = (int)(TILE * MINIMAP_SCALE);
	px = MINIMAP_X + (int)(game->player.x * MINIMAP_SCALE);
	py = MINIMAP_Y + (int)(game->player.y * MINIMAP_SCALE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(px + i, py + j, 0xFF0000, game);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	c;

	y = 0;
	while (y < game->map.m_height)
	{
		x = 0;
		while (x < game->map.m_width && game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (c == '1')
				color = 0x404040;
			else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				color = 0xAAAAAA;
			else
				color = 0x000000;
			draw_tile(game, x, y, color);
			x++;
		}
		y++;
	}
	draw_player_minimap(game);
}
