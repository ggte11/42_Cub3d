/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:07:40 by mcardoso          #+#    #+#             */
/*   Updated: 2026/04/30 15:47:04 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_tex_color(t_image *tex, int x, int y)
{
	int	offset;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	offset = y * tex->size_line + x * (tex->bpp / 8);
	return (*(int *)(tex->data + offset));
}

static int	get_tex_idx(t_game *game, int side)
{
	if (side == 0)
	{
		if (game->ray.dir_x > 0)
			return (EA);
		return (WE);
	}
	else
	{
		if (game->ray.dir_y > 0)
			return (SO);
		return (NO);
	}
}

static int	get_tex_x(t_game *game, float dist, int side, int tex_idx)
{
	float	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = (game->player.y / BLOCK) + dist * game->ray.dir_y;
	else
		wall_x = (game->player.x / BLOCK) + dist * game->ray.dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * game->texture.img[tex_idx].width);
	if (side == 0 && game->ray.dir_x < 0)
		tex_x = game->texture.img[tex_idx].width - tex_x - 1;
	if (side == 1 && game->ray.dir_y > 0)
		tex_x = game->texture.img[tex_idx].width - tex_x - 1;
	return (tex_x);
}

static void	draw_colum_util(t_game *game, int x, t_col_draw *d)
{
	int	tex_y;

	while (d->y <= d->end)
	{
		tex_y = (int)d->tex_pos;
		put_pixel(x, d->y, get_tex_color(&game->texture.img[d->tex_idx],
				d->tex_x, tex_y), game);
		d->tex_pos += d->step;
		d->y++;
	}
}

void	draw_tex_colum(t_game *game, int x, int st, int end)
{
	int			side;
	float		dist;
	t_col_draw	d;

	side = game->ray.side;
	if (side == 0)
		dist = game->ray.side_dist_x - game->ray.delta_x;
	else
		dist = game->ray.side_dist_y - game->ray.delta_y;
	d.tex_idx = get_tex_idx(game, side);
	d.tex_x = get_tex_x(game, dist, side, d.tex_idx);
	d.step = (float)game->texture.img[d.tex_idx].height / (float)(end - st + 1);
	d.tex_pos = 0.0f;
	if (st < 0)
	{
		d.tex_pos = -st * d.step;
		st = 0;
	}
	if (end >= SHEIGHT)
		end = SHEIGHT - 1;
	d.y = st;
	d.end = end;
	draw_colum_util(game, x, &d);
}
