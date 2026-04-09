#include "../cub3d.h"

void	draw_square(int xy[2], int size, int color, t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel(xy[0] + i, xy[1] + j, color, game);
			i++;
		}
		j++;
	}
}

bool	can_move_to(t_game *game, float x, float y, float r)
{
	return (!touch_wall(x - r, y - r, game) \
&& !touch_wall(x + r, y - r, game) \
&& !touch_wall(x - r, y + r, game) \
&& !touch_wall(x + r, y + r, game));
}

float	get_spawn_angle(char dir)
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
