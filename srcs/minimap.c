#include "../cub3d.h"

void	init_minimap(t_game *game)
{
	game->mm.x = MINIMAP_X;
	game->mm.y = MINIMAP_Y;
	game->mm.t_size = (int)(TILE * MINIMAP_SCALE);
	game->mm.width = game->map.m_width * game->mm.t_size;
	game->mm.height = game->map.m_height * game->mm.t_size;
}

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < game->mm.t_size)
	{
		j = 0;
		while (j < game->mm.t_size)
		{
			px =  game->mm.x + (x * game->mm.t_size) + i;
			py = game->mm.y + (y * game->mm.t_size) + j;
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

	size = game->mm.t_size;
	px = MINIMAP_X + (int)(game->player.x / BLOCK * size);
	py = MINIMAP_Y + (int)(game->player.y / BLOCK * size);
	if (px < game->mm.x || px > game->mm.x + game->mm.width)
		return ;
	if (py < game->mm.y || py > game->mm.y + game->mm.height)
		return ;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (px + i >= game->mm.x && px + i <= game->mm.x + game->mm.width
				&& py + j >= game->mm.y && py + j <= game->mm.y + game->mm.height)
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
