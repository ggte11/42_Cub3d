#include "../cub3d.h"

void	clean_config(t_game *game)
{
	free(game->config.no_text);
	free(game->config.so_text);
	free(game->config.ea_text);
	free(game->config.we_text);
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
