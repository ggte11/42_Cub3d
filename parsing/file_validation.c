#include "../cub3d.h"

static int	check_ext(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	parse_file(t_game *game, char *filename)
{
	if (!check_ext(filename))
		return (print_error("Invalid file name, must be *.cub"));
	game->fd = open_file(filename);
	if (game->fd < 0)
		return (print_error("Cannot open file"));
	return (0);
}
