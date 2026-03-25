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

static int	get_tex_dir(t_game *game, int side)
{
	if (side == 0)
	{
		if (game->ray.dir_x > 0)
			return (WE);
		return (EA);
	}
	else
	{
		if (game->ray.dir_y > 0)
			return (NO);
		return (SO);
	}
}

static int	get_tex_x(t_game *game, float dist, int side, int tex_idx)
{
	float	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = (game->player.y / BLOCK) + 
}
