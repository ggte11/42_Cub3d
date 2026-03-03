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

int	draw_loop(t_game *game)
{
	move_player(&game->player);
	clear_image(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
	return (0);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map.grid = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SWIDTH, SHEIGHT, "cub3d");
	game->image.img = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	game->image.data = mlx_get_data_addr(game->image.img, &game->image.bpp,
		&game->image.size_line, &game->image.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}
