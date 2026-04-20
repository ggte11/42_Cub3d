/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:07:45 by mcardoso          #+#    #+#             */
/*   Updated: 2026/04/20 17:31:24 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		pos[2];

	map = game->map.grid;
	color = 0x0000FF;
	pos[1] = 0;
	while (map[pos[1]])
	{
		pos[0] = 0;
		while (map[pos[1]][pos[0]])
		{
			if (map[pos[1]][pos[0]] == '1')
				draw_square((int [2]){pos[0] * BLOCK, pos[1] * BLOCK},
					BLOCK, color, game);
			pos[0]++;
		}
		pos[1]++;
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
		return (on_destroy(game));
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
