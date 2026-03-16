#include "../cub3d.h"

static int	is_wall_cell(t_game *game, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || !game->map.grid[map_y])
		return (1);
	row_len = ft_strlen(game->map.grid[map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (1);
	return (game->map.grid[map_y][map_x] == '1');
}

// Initializes ray direction and delta distances
static void	init_ray_dir(t_rays *ray, float angle)
{
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	if (ray->dir_x == 0)
		ray->delta_x = INFINITY;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = INFINITY;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
}

static void	init_step_side(t_rays *ray, float pos_x, float pos_y, int map[2])
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - map[0]) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (map[0] + 1.0f - pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - map[1]) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (map[1] + 1.0f - pos_y) * ray->delta_y;
	}
}

static void	run_dda(t_game *game, t_rays *ray ,int map[2])
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x +=ray->delta_x;
			map[0] += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			map[1] += ray->step_y;
			ray->side = 1;
		}
		if (is_wall_cell(game, map[0], map[1]))
			break ;
	}
}

float	cast_ray_dda(t_game *game, float angle, int *side)
{
	float	pos_x;
	float	pos_y;
	int		map[2];
	float	dist;

	pos_x = game->player.x / BLOCK;
	pos_y = game->player.y / BLOCK;
	map[0] = (int)pos_x;
	map[1] = (int)pos_y;
	init_ray_dir(&game->ray, angle);
	init_step_side(&game->ray, pos_x, pos_y, map);
	run_dda(game, &game->ray, map);
	if (game->ray.side == 0)
		dist = (map[0] - pos_x + (1 - game->ray.step_x) * 0.5f) / game->ray.dir_x;
	else
		dist = (map[1] - pos_y + (1 - game->ray.step_y) * 0.5f) / game->ray.dir_y;
	if (side)
		*side = game->ray.side;
	return (dist);
}
