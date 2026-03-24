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
	int i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}
