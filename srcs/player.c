#include "../cub3d.h"

void	init_player(t_player *player)
{
	player->x = SWIDTH / 2;
	player->y = SHEIGHT / 2;
	player->angle = 0;
	player->key.w = false;
	player->key.s = false;
	player->key.a = false;
	player->key.d = false;
	player->key.l_arrow = false;
	player->key.r_arrow = false;
}

void	move_player(t_player *player)
{
	float	speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 10;
	angle_speed = 0.1;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key.l_arrow)
		player->angle -= angle_speed;
	if (player->key.r_arrow)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key.w)
		player->y -= speed;
	if (player->key.s)
		player->y += speed;
	if (player->key.a)
		player->x -= speed;
	if (player->key.d)
		player->x += speed;
}

void	draw_square(int x, int y, int size, int color ,t_game *game)
{
	int	i;

	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, game);
}
