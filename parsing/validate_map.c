#include "../cub3d.h"

int normalize_row(char **row, int row_len, int map_width)
{
	char *n_row;

	n_row = malloc(sizeof(char) * map_width + 1);
	if (!n_row)
		return (print_error(ALL_ERR), 0);
	ft_memset(n_row, ' ', map_width);
	n_row[map_width] = '\0';
	ft_memcpy(n_row, *row, row_len);
	free(*row);
	*row = n_row;
	return (1);
}

int normalize_map(t_map *map)
{
	int i;
	int row_len;

	i = 0;
	while(map->grid[i])
	{
		row_len = ft_strlen(map->grid[i]);
		if (row_len < map->width)
			if (!normalize_row(&map->grid[i], row_len, map->width))
				return (0);
		i++;
	}
	return (1);
}

void validate_map(t_map *map)
{
	if (!normalize_map(map))
		return ; //Allocation error
}