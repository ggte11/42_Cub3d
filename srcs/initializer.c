#include "../cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	i;

	if (x >= SWIDTH || y >= SHEIGHT || x < 0 || y < 0)
		return ;
	i = y * game->image.size_line + x * game->image.bpp / 8;
	game->image.data[i] = color & 0xFF;
	game->image.data[i + 1] = (color >> 8) & 0xFF;
	game->image.data[i + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < SWIDTH * SHEIGHT * (game->image.bpp / 8))
	{
		game->image.data[i] = 0;
		i++;
	}
}

char	**get_map(void)
{
	char	**map = malloc(sizeof(char *) * 11);
	map[0] = "11111111111111";
	map[1] = "10000000000001";
	map[2] = "10000000000001";
	map[3] = "10000000000001";
	map[4] = "10000001000001";
	map[5] = "10000001000001";
	map[6] = "10000001000001";
	map[7] = "11111111000001";
	map[8] = "10000000000001";
	map[9] = "11111111111111";
	map[10] = NULL;
	return (map);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = game->map.grid;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_game *game)
{
	float	fraction;
	float	start_x;
	int		i;

	move_player(&game->player);
	clear_image(game);
	fraction = PI / 3 / SWIDTH;
	start_x = game->player.angle - PI / 6;
	i = 0;
	while (i < SWIDTH)
	{
		draw_line(&game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
	return (0);
}

void	init_game(t_game *game)
{
	init_player(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SWIDTH, SHEIGHT, "cub3d");
	game->image.img = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	game->image.data = mlx_get_data_addr(game->image.img, &game->image.bpp,
		&game->image.size_line, &game->image.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}
