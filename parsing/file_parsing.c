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
	if (*line == 'F' && line[1] == ' ')
		return (F);
	if (*line == 'C' && line[1] == ' ')
		return (C);
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

int save_wall_text(t_game *game, char *wall, t_token type)
{
	unsigned int i;
	char *text;

	i = (unsigned)skipwhitespace(wall, 2);
	if (!wall[i])
		return (0);
	text = ft_substr(wall, i, ft_strlen(wall + i) + 1);
	if (!text)
		return (0);
	if (access(text, O_RDONLY))
		return (free(text), 0);
	if (type == NO && !game->config.no_text)
		return (game->config.no_text = text, 1);
	if (type == SO && !game->config.so_text)
		return (game->config.so_text = text, 1);
	if (type == WE && !game->config.we_text)
		return (game->config.we_text = text, 1);
	if (type == EA && !game->config.ea_text)
		return (game->config.ea_text = text, 1);
	return (free(text), 0);
}

int save_color(t_game *game, char *color, t_token type)
{
	int i;
	int R;
	int G;
	int B;

	R = 0;
	G = 0;
	B = 0;
	i = skipwhitespace(color, 1);
	while (color[i] && color[i] != ',')
	{
		if (!ft_isdigit(color[i]))
			return (0);
		R = R * 10 + (color[i] - '0');
		i++;
	}
	i++;
	while (color[i] && color[i] != ',')
	{
		if (!ft_isdigit(color[i]))
			return (0);
		G = G * 10 + (color[i] - '0');
		i++;
	}
	i++;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (0);
		B = B * 10 + (color[i] - '0');
		i++;
	}
	if (type == F)
		return (game->config.floor_color = ((R << 16) | (G << 8) | B), 1);
	if (type == C)
		return (game->config.ceiling_color = ((R << 16) | (G << 8) | B), 1);
	return (0);
}

int process_line(t_game *game, char *line)
{
	int i;
	t_token type;

	i = skipwhitespace(line, 0);
	if (!line[i])
		return (free(line), 0);
	type = find_token_type(line + i);
	if (type == ERROR)
		return (free(line), 0);
	if (type >= 0 && type <= 3)
		if (!save_wall_text(game, line + i, type))
			return (free(line), 0);
	if (type == 4 || type == 5)
		if (!save_color(game, line + i, type))
			return (free(line), 0);
	if (line[i] == '1')
		return (free(line), 0);
	return (free(line), 1);
}

int extract_data(t_game *game)
{
	char *line;
	size_t line_len;

	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			return 0;
		if (*line != '\n')
		{
			line_len = ft_strlen(line);
			line[line_len - 1] = 0;
			if (!process_line(game, line))
				return 1;
			line[line_len - 1] = '\n';
		}
	}
}
