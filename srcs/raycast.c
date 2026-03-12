#include "../cub3d.h"

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

