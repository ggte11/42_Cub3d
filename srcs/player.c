/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:07:56 by mcardoso          #+#    #+#             */
/*   Updated: 2026/04/16 16:07:57 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	update_angle(t_player *player)
{
	if (player->key.l_arrow)
		player->angle -= ROT_SPEED;
	if (player->key.r_arrow)
		player->angle += ROT_SPEED;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

static void	move_vector(t_player *player, float *move_x, float *move_y)
{
	*move_x = 0.0f;
	*move_y = 0.0f;
	if (player->key.w)
	{
		*move_x += cos(player->angle) * MOVE_SPEED;
		*move_y += sin(player->angle) * MOVE_SPEED;
	}
	if (player->key.s)
	{
		*move_x -= cos(player->angle) * MOVE_SPEED;
		*move_y -= sin(player->angle) * MOVE_SPEED;
	}
	if (player->key.a)
	{
		*move_x += sin(player->angle) * MOVE_SPEED;
		*move_y -= cos(player->angle) * MOVE_SPEED;
	}
	if (player->key.d)
	{
		*move_x -= sin(player->angle) * MOVE_SPEED;
		*move_y += cos(player->angle) * MOVE_SPEED;
	}
}

static void	apply_mov(t_game *game, float move_x, float move_y)
{
	float	next_x;
	float	next_y;
	float	radius;

	radius = 8.0f;
	next_x = game->player.x + move_x;
	next_y = game->player.y;
	if (can_move_to(game, next_x, next_y, radius))
		game->player.x = next_x;
	next_x = game->player.x;
	next_y = game->player.y + move_y;
	if (can_move_to(game, next_x, next_y, radius))
		game->player.y = next_y;
}

void	move_player(t_game *game)
{
	float	move_x;
	float	move_y;

	update_angle(&game->player);
	move_vector(&game->player, &move_x, &move_y);
	apply_mov(game, move_x, move_y);
}
