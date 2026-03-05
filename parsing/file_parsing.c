#include "../cub3d.h"

int skipwhitespace(char *str, int pos)
{
	int i;

	i = pos;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return i;
}

int	count_elems(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
			count++;
		i++;
	}
	return (count);
}

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

int save_wall_text(t_game *game, char *wall, t_token type)
{
	unsigned int i;
	char *text;

	if (count_elems(wall) != 2)
		return (print_error(FORM_ERR), 0);
	i = (unsigned)skipwhitespace(wall, 2);
	if (!wall[i])
		return (print_error(FORM_ERR), 0);
	text = ft_substr(wall, i, ft_strlen(wall + i) + 1);
	if (!text)
		return (print_error(ALL_ERR), 0);
	if (access(text, O_RDONLY))
		return (print_error(MISS_TEXT), free(text), 0);
	if (type == NO && !game->config.no_text)
		return (game->config.no_text = text, 1);
	if (type == SO && !game->config.so_text)
		return (game->config.so_text = text, 1);
	if (type == WE && !game->config.we_text)
		return (game->config.we_text = text, 1);
	if (type == EA && !game->config.ea_text)
		return (game->config.ea_text = text, 1);
	return (print_error(DBL_TEXT), free(text), 0);
}

static int parse_color_code(char *color, int *i)
{
	int value;
	int delta_i;

	value = 0;
	delta_i = 0;
	while (color[*i] && color[*i] != ',')
	{
		if (!ft_isdigit(color[*i]))
			return (-1);
		value = value * 10 + (color[*i] - '0');
		(*i)++;
		delta_i++;
	}
	if ((delta_i == 0 || delta_i > 3) || value > 255)
		return (-1);
	(*i)++;
	return (value);
}

int save_color(t_game *game, char *color, t_token type)
{
	int i;
	int R;
	int G;
	int B;

	if (count_elems(color) != 2)
		return (print_error(FORM_ERR), 0);
	i = skipwhitespace(color, 1);
	R = parse_color_code(color, &i);
	G = parse_color_code(color, &i);
	B = parse_color_code(color, &i);
	if (R == -1 || G == -1 || B == -1)
		return (print_error(RGB_ERR), 0);
	if (type == F && game->config.floor_color == -1)
		return (game->config.floor_color = ((R << 16) | (G << 8) | B), 1);
	if (type == C && game->config.ceiling_color == -1)
		return (game->config.ceiling_color = ((R << 16) | (G << 8) | B), 1);
	return (print_error(DBL_COLOR), 0);
}

int process_line(t_game *game, char *line)
{
	int i;
	t_token type;

	if (*line == '\0')
		return (free(line), 1);
	i = skipwhitespace(line, 0);
	if (!line[i])
		return (free(line), 0);
	type = find_token_type(line + i);
	if (type == ERROR)
		return (free(line), print_error(TYP_ERR), 0);
	if (type >= NO && type <= EA)
		if (!save_wall_text(game, line + i, type))
			return (free(line), 0);
	if (type == F || type == C)
		if (!save_color(game, line + i, type))
			return (free(line), 0);
	if (type == MAP)
	{
		if (check_config(game))
			return (2);
		else
			return (free(line), 0);
	}
	return (free(line), 1);
}

char	*buildline(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	totallen;
	char	*final_s;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	totallen = len1 + len2 + sizeof(char);
	final_s = (char *)malloc(sizeof(char) * totallen);
	if (final_s == NULL)
		return (NULL);
	if (*s1)
		ft_strlcpy(final_s, s1, totallen);
	ft_strlcat(final_s, s2, totallen);
	return (final_s);
}

void extract_map(t_game *game)
{
	

}

void extract_data(t_game *game)
{
	char *line;
	size_t line_len;
	int process_ret;

	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			return ;
		line_len = ft_strlen(line);
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		process_ret = process_line(game, line);
		if (process_ret == 2)
			break ;
		else if (!process_ret)
			return ;
	}
	extract_map(game);
}
