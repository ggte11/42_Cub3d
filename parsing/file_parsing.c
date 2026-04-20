/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:36:11 by ddamiba           #+#    #+#             */
/*   Updated: 2026/04/20 13:53:53 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	save_wall_text(t_game *game, char *wall, t_token type)
{
	unsigned int	i;
	char			*text;

	if (count_elems(wall) != 2)
		return (print_error(FORM_ERR), 0);
	i = (unsigned)skipwhitespace(wall, 2);
	if (!wall[i])
		return (print_error(FORM_ERR), 0);
	text = ft_substr(wall, i, ft_strlen(wall + i) + 1);
	if (!text)
		return (print_error(ALL_ERR), 0);
	if (!check_ext(text, ".xpm"))
		return (print_error(TEXT_EXT), free(text), 0);
	if (access(text, O_RDONLY))
		return (print_error(MISS_TEXT), free(text), 0);
	if (type == NO && !game->texture.path[NO])
		return (game->texture.path[NO] = text, 1);
	if (type == SO && !game->texture.path[SO])
		return (game->texture.path[SO] = text, 1);
	if (type == WE && !game->texture.path[WE])
		return (game->texture.path[WE] = text, 1);
	if (type == EA && !game->texture.path[EA])
		return (game->texture.path[EA] = text, 1);
	return (print_error(DBL_TEXT), free(text), 0);
}

int	save_color(t_game *game, char *color, t_token type)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (count_elems(color) != 2)
		return (print_error(FORM_ERR), 0);
	i = skipwhitespace(color, 1);
	r = parse_color_code(color, &i);
	g = parse_color_code(color, &i);
	b = parse_color_code(color, &i);
	if (color[i])
		return (print_error(RGB_ERR), 0);
	if (r == -1 || g == -1 || b == -1)
		return (print_error(RGB_ERR), 0);
	if (type == F && game->texture.floor_color == -1)
		return (game->texture.floor_color = ((r << 16) | (g << 8) | b), 1);
	if (type == C && game->texture.ceiling_color == -1)
		return (game->texture.ceiling_color = ((r << 16) | (g << 8) | b), 1);
	return (print_error(DBL_COLOR), 0);
}

int	process_line(t_game *game, char *line)
{
	int		i;
	t_token	type;

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

void	extract_map(t_game *game, char *map_start)
{
	char	*line;
	char	*map;
	int		line_len;

	map = NULL;
	line = map_start;
	while (1)
	{
		map = buildline(map, line);
		if (!map)
			return (print_error(ALL_ERR));
		line = get_next_line(game->fd);
		if (!line)
			break ;
		line_len = ft_strlen(line) - 1;
		if (line_len == 0)
			return (free(line), free(map), print_error(MAP_ERR));
		if (line_len > game->map.m_width)
			game->map.m_width = line_len;
		game->map.m_height++;
	}
	game->map.grid = ft_split(map, '\n');
	free(map);
	if (!game->map.grid)
		print_error("Allocation error");
}

void	extract_data(t_game *game)
{
	char	*line;
	size_t	line_len;
	int		process_ret;

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
	game->map.m_width = ft_strlen(line);
	line[line_len - 1] = '\n';
	extract_map(game, line);
}
