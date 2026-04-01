#include "../cub3d.h"

void	clean_config(t_game *game)
{
	free(game->texture.path[NO]);
	free(game->texture.path[SO]);
	free(game->texture.path[WE]);
	free(game->texture.path[EA]);
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
	map = NULL;
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
	exit(0);
	return (0);
}
