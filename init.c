/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martim <martim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:08:13 by mcardoso          #+#    #+#             */
/*   Updated: 2026/04/16 20:28:26 by martim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_image(t_game *game)
{
	game->image.img = NULL;
	game->image.data = NULL;
	game->image.size_line = 0;
	game->image.bpp = 0;
	game->image.endian = 0;
	game->image.width = 0;
	game->image.height = 0;
}

static void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	game->texture.path[NO] = NULL;
	game->texture.path[SO] = NULL;
	game->texture.path[WE] = NULL;
	game->texture.path[EA] = NULL;
	while (i < DIR_COUNT)
	{
		game->texture.img[i].img = NULL;
		game->texture.img[i].data = NULL;
		game->texture.img[i].size_line = 0;
		game->texture.img[i].bpp = 0;
		game->texture.img[i].endian = 0;
		game->texture.img[i].width = 0;
		game->texture.img[i].height = 0;
		i++;
	}
	game->texture.floor_color = -1;
	game->texture.ceiling_color = -1;
}

static void	init_map(t_game *game)
{
	game->map.grid = NULL;
	game->map.m_width = 0;
	game->map.m_height = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';
}

void	init_config(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->fd = -1;
	init_textures(game);
	init_image(game);
	init_map(game);
}
