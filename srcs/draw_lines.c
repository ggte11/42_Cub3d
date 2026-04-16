/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:07:37 by mcardoso          #+#    #+#             */
/*   Updated: 2026/04/16 16:07:38 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_wall_height(float dist)
{
	if (dist < 0.001f)
		dist = 0.001f;
	return ((int)(SHEIGHT / dist));
}

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

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SHEIGHT / 2)
	{
		x = 0;
		while (x < SWIDTH)
		{
			put_pixel(x, y, game->texture.ceiling_color, game);
			x++;
		}
		y++;
	}
	while (y < SHEIGHT)
	{
		x = 0;
		while (x < SWIDTH)
		{
			put_pixel(x, y, game->texture.floor_color, game);
			x++;
		}
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float angle, int x)
{
	float	dist;
	float	corr_dist;
	float	angle_diff;
	int		side;
	int		height;

	dist = cast_ray_dda(game, angle, &side);
	angle_diff = angle - player->angle;
	if (angle_diff > PI)
		angle_diff -= 2 * PI;
	else if (angle_diff < -PI)
		angle_diff += 2 * PI;
	corr_dist = dist * cos(angle_diff);
	height = get_wall_height(corr_dist);
	draw_tex_colum(game, x, (SHEIGHT - height) / 2,
		(SHEIGHT + height) / 2);
}
