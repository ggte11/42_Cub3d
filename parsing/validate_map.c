/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:37:05 by ddamiba           #+#    #+#             */
/*   Updated: 2026/03/23 18:09:13 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_bounds(char *bound)
{
	int	i;

	i = 0;
	while (bound[i])
	{
		if (bound[i] != '1' && bound[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map_char(char c)
{
	if (c == '1')
		return (1);
	if (c == '0')
		return (1);
	if (c == ' ')
		return (1);
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'W')
		return (1);
	return (0);
}

int	validate_pos(char map_c, t_map *map, int row, int col)
{
	if ((map_c == ' ' || map_c == '1'))
		return (1);
	if (col == 0 || col == map->m_width - 1)
		return (0);
	if (map->grid[row][col - 1] == ' ' || map->grid[row][col + 1] == ' ')
		return (0);
	if (map->grid[row - 1][col] == ' ' || map->grid[row + 1][col] == ' ')
		return (0);
	if (map_c != '0')
	{
		if (map->player_dir == '\0')
		{
			map->player_dir = map_c;
			map->player_x = col;
			map->player_y = row;
		}
		else
			return (print_error(DBL_PLAYER), 0);
	}
	return (1);
}

int	validate_row(t_map *map, int row)
{
	int		c_i;
	char	map_c;

	if (row == 0 || row == map->m_height)
	{
		if (check_bounds(map->grid[row]))
			return (1);
		else
			return (print_error(MAP_ERR), 0);
	}
	c_i = skipwhitespace(map->grid[row], 0);
	while (map->grid[row][c_i])
	{
		map_c = map->grid[row][c_i];
		if (!is_valid_map_char(map_c))
			return (print_error(M_TYP_ERR), 0);
		else if (!validate_pos(map_c, map, row, c_i))
			return (print_error(MAP_ERR), 0);
		c_i++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	int	r_i;

	if (!map->grid)
		return (0);
	if (!normalize_map(map))
		return (0);
	r_i = 0;
	while (map->grid[r_i])
	{
		if (!validate_row(map, r_i))
			return (0);
		r_i++;
	}
	if (!map->player_dir)
		return (print_error(MISS_PLAYER), 0);
	return (1);
}
