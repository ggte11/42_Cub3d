#include "../cub3d.h"

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

	move_player(game);
	draw_background(game);
	fraction = PI / 3 / SWIDTH;
	start_x = game->player.angle - PI / 6;
	i = 0;
	while (i < SWIDTH)
	{
		draw_line(&game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
	return (0);
}

void	init_game(t_game *game)
{
	init_player(game);
	init_minimap(game);
	game->mlx = mlx_init();
	if (!game->mlx || !load_textures(game))
		exit(1);
	game->win = mlx_new_window(game->mlx, SWIDTH, SHEIGHT, "cub3D");
	game->image.img = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	game->image.data = mlx_get_data_addr(game->image.img, &game->image.bpp,
		&game->image.size_line, &game->image.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}

void	init_player(t_game *game)
{
	game->player.x = (game->map.player_x + 0.5f) * BLOCK;
	game->player.y = (game->map.player_y + 0.5f) * BLOCK;
	game->player.angle = get_spawn_angle(game->map.player_dir);
	game->player.key.w = false;
	game->player.key.s = false;
	game->player.key.a = false;
	game->player.key.d = false;
	game->player.key.l_arrow = false;
	game->player.key.r_arrow = false;
}
