#include "../cub3d.h"

void	draw_line(t_player *player, t_game *game, float start_x)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch_wall(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}
