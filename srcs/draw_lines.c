#include "../cub3d.h"

static int	get_wall_height(float dist)
{
	if (dist < 0.001f)
		dist = 0.001f;
	return ((int)(SHEIGHT / dist));
}

/* static void	draw_vertical(t_game *game, int x, int start, int end, int color)
{
	int	y;

	if (start < 0)
		start = 0;
	if (end >= SHEIGHT)
		end = SHEIGHT - 1;
	y = start;
	while (y <= end)
	{
		put_pixel(x, y, color, game);
		y++;
	}
} */

void	draw_line(t_player *player, t_game *game, float angle, int x)
{
	float	dist;
	float	corr_dist;
	float	angle_diff;
	int		side;
	int		height;
	int		start;
	int		end;

	dist = cast_ray_dda(game, angle, &side);
	angle_diff = angle - player->angle;
	if (angle_diff > PI)
		angle_diff -= 2 * PI;
	else if (angle_diff < -PI)
		angle_diff += 2 * PI;
	corr_dist = dist * cos(angle_diff);
	height = get_wall_height(corr_dist);
	start = (SHEIGHT - height) / 2;
	end = (SHEIGHT + height) / 2;
	draw_tex_colum(game, x, start, end);
}
