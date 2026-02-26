#include "../cub3d.h"

int skipwhitespace(char *str, int pos)
{
	int i;

	i = pos;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return i;
}

t_token find_token_type(char *line)
{
	if (*line = 'F' && line[1] == ' ')
		return (F);
	if (*line = 'C' && line[1] == ' ')
		return (C);
	if (!ft_strncmp(line, "NO", 2) && line[2] == ' ')
		return (NO);
	if (!ft_strncmp(line, "SO", 2) && line[2] == ' ')
		return (SO);
	if (!ft_strncmp(line, "WE", 2) && line[2] == ' ')
		return (WE);
	if (!ft_strncmp(line, "EA", 2) && line[2] == ' ')
		return (EA);
	return (-1);
}

void save_wall_text(t_game *game, char *wall)
{
	
}

int process_line(t_game *game, char *line)
{
	int i;
	t_token type;

	i = skipwhitespace(line, i);
	if (!line[i])
		return (free(line), 0);
	type = find_token_type(line + i);
	if (type == -1)
		return (free(line), 0);
		save_wall_text(game, line + i);

		save_color(game, line + i);
	if (line[i] = '1');
		return (free(line), 0);
}

int extract_data(t_game *game)
{
	char *line;

	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			return 0;
		process_line(game, line);
	}
}
