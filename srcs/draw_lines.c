#include "../cub3d.h"

static float	distance(float x, float y)
{
	return (sqrt((x * x) + (y * y)));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x = x2 - x1;
	float	delta_y = y2 - y1;
	float	angle = atan2(delta_y, delta_x) - game->player.angle;
	float	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch_wall(ray_x, ray_y, game))
	{
		//put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	float	height = (BLOCK / dist) * (SWIDTH / 2);
	int		start_y = (SHEIGHT - height) / 2;
	int		end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 0x0000FF, game);
		start_y++;
	}
}
