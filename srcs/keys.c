#include "../cub3d.h"

int	key_press(int keycode, t_player *player)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == W)
		player->key.w = true;
	if (keycode == S)
		player->key.s = true;
	if (keycode == A)
		player->key.a = true;
	if (keycode == D)
		player->key.d = true;
	if (keycode == ARROW_LEFT)
		player->key.l_arrow = true;
	if (keycode == ARROW_RIGHT)
		player->key.r_arrow = true;
	return (0);
}

int	key_realease(int keycode, t_player *player)
{
	if (keycode == W)
		player->key.w = false;
	if (keycode == S)
		player->key.s = false;
	if (keycode == A)
		player->key.a = false;
	if (keycode == D)
		player->key.d = false;
	if (keycode == ARROW_LEFT)
		player->key.l_arrow = false;
	if (keycode == ARROW_RIGHT)
		player->key.r_arrow = false;
	return (0);
}
