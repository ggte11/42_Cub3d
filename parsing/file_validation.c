#include "../cub3d.h"

int	check_ext(char *filename, char *ext)
{
	int	flen;
	int	elen;

	flen = ft_strlen(filename);
	elen = ft_strlen(ext);
	if (flen <= elen)
		return (0);
	if (ft_strncmp(filename + flen - elen, ext, elen) != 0)
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
	if (!check_ext(filename, ".cub"))
		return (print_error("Invalid file name, must be *.cub"), 1);
	game->fd = open_file(filename);
	if (game->fd < 0)
		return (print_error("Cannot open file"), 1);
	return (0);
}
