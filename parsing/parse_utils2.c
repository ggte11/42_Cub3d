#include "../cub3d.h"

t_token find_token_type(char *line)
{
	if (*line == 'F' && line[1] == ' ')
		return (F);
	if (*line == 'C' && line[1] == ' ')
		return (C);
	if (*line == '1')
		return (MAP);
	if (!ft_strncmp(line, "NO", 2) && line[2] == ' ')
		return (NO);
	if (!ft_strncmp(line, "SO", 2) && line[2] == ' ')
		return (SO);
	if (!ft_strncmp(line, "WE", 2) && line[2] == ' ')
		return (WE);
	if (!ft_strncmp(line, "EA", 2) && line[2] == ' ')
		return (EA);
	return (ERROR);
}
