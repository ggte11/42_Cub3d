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

	speed = 1.5;
	if (player->key.w)
		player->y -= speed;
	if (player->key.s)
		player->y += speed;
	if (player->key.a)
		player->x -= speed;
	if (player->key.d)
		player->x += speed;
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = game->player.x;
	y = game->player.y;
	i = -5;
	while (i < 5)
	{
		j = -5;
		while (j < 5)
		{
			put_pixel(x + i, y + j, 0x00FF00, game);
			j++;
		}
		i++;
	}
}
