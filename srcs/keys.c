#include "../cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		return (on_destroy(game));
	if (keycode == W)
		game->player.key.w = true;
	if (keycode == S)
		game->player.key.s = true;
	if (keycode == A)
		game->player.key.a = true;
	if (keycode == D)
		game->player.key.d = true;
	if (keycode == ARROW_LEFT)
		game->player.key.l_arrow = true;
	if (keycode == ARROW_RIGHT)
		game->player.key.r_arrow = true;
	return (0);
}

int	key_realease(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key.w = false;
	if (keycode == S)
		game->player.key.s = false;
	if (keycode == A)
		game->player.key.a = false;
	if (keycode == D)
		game->player.key.d = false;
	if (keycode == ARROW_LEFT)
		game->player.key.l_arrow = false;
	if (keycode == ARROW_RIGHT)
		game->player.key.r_arrow = false;
	return (0);
}
