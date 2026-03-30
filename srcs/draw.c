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

void	draw_tex_colum(t_game *game, int x, int start, int end)
{
	int		y;
	int		side;
	int		tex_idx;
	int		height;
	int		tex_x;
	float	dist;
	float	step;
	float	tex_pos;
	int		tex_y;

	side = game->ray.side;
	if (side == 0)
		dist = game->ray.side_dist_x - game->ray.delta_x;
	if (side == 1)
		dist = game->ray.side_dist_y - game->ray.delta_y;
	tex_idx = get_tex_idx(game, side);
	height = end - start + 1;
	tex_x = get_tex_x(game, dist, side, tex_idx);
	step = (float)game->texture.img[tex_idx].height / (float)height;
	tex_pos = 0.0f;
	if (start < 0)
	{
		tex_pos = -start * step;
		start = 0;
	}
	if (end >= SHEIGHT)
		end = SHEIGHT - 1;
	y = start;
	while (y <= end)
	{
		tex_y = (int)tex_pos;
		put_pixel(x, y, get_tex_color(&game->texture.img[tex_idx],tex_x, tex_y), game);
		tex_pos += step;
		y++;
	}
}
