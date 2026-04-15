#include "../cub3d.h"

static void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < DIR_COUNT)
	{
		if (game->texture.path[i] && game->texture.img[i].img)
		{
			mlx_destroy_image(game->mlx, game->texture.img[i].img);
			game->texture.img[i].img = NULL;
		}
		i++;
	}
}

void	clean_config(t_game *game)
{
	destroy_textures(game);
	free(game->texture.path[NO]);
	free(game->texture.path[SO]);
	free(game->texture.path[WE]);
	free(game->texture.path[EA]);
	game->texture.path[NO] = NULL;
	game->texture.path[SO] = NULL;
	game->texture.path[WE] = NULL;
	game->texture.path[EA] = NULL;
}

void	clean_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < SWIDTH * SHEIGHT * (game->image.bpp / 8))
	{
		game->image.data[i] = 0;
		i++;
	}
}

int	on_destroy(t_game *game)
{
	clean_map(game->map.grid);
	clean_config(game);
	if (game->mlx)
	{
		if (game->image.img)
			mlx_destroy_image(game->mlx, game->image.img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}
