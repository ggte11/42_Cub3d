#include "../cub3d.h"

static float	get_spawn_angle(char dir)
{
	if (dir == 'N')
		return (3 * PI / 2);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'E')
		return (0.0f);
	if (dir == 'W')
		return (PI);
	return (0.0f);
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

void	move_player(t_player *player)
{
	float	speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = MOVE_SPEED;
	angle_speed = ROT_SPEED;
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
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key.s)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key.a)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key.d)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}

void	draw_square(int x, int y, int size, int color ,t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel(x + i, y + j, color, game);
			i++;
		}
		j++;
	}
}
