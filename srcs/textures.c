/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:08:01 by mcardoso          #+#    #+#             */
/*   Updated: 2026/04/16 16:08:02 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	load_texture(t_game *game, int dir)
{
	game->texture.img[dir].img = mlx_xpm_file_to_image(game->mlx,
			game->texture.path[dir], &game->texture.img[dir].width,
			&game->texture.img[dir].height);
	if (!game->texture.img[dir].img)
		return (print_error("Failed to load texture image"), 0);
	game->texture.img[dir].data = mlx_get_data_addr(game->texture.img[dir].img,
			&game->texture.img[dir].bpp, &game->texture.img[dir].size_line,
			&game->texture.img[dir].endian);
	if (!game->texture.img[dir].data)
		return (print_error("Failed to access texture data"), 0);
	return (1);
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < DIR_COUNT)
	{
		if (!load_texture(game, i))
			return (0);
		i++;
	}
	return (1);
}
