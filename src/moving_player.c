/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:56:18 by omalovic          #+#    #+#             */
/*   Updated: 2025/10/16 13:56:37 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	rotate_player(t_game *game, int direction)
{
	double	angle;
	double	cos_a;
	double	sin_a;
	double	tmp;

	angle = 0.03 * direction;
	cos_a = cos(angle);
	sin_a = sin(angle);
	tmp = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = tmp * sin_a + game->player.dir_y * cos_a;
	tmp = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = tmp * sin_a + game->player.plane_y * cos_a;
}

void	move_player(t_game *game, int direction)
{
	double	speed;
	double	next_x;
	double	next_y;

	speed = 0.05 * direction;
	next_x = game->player.x + game->player.dir_x * speed;
	next_y = game->player.y + game->player.dir_y * speed;
	if (game->data->map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
	if (game->data->map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
}

void	strafe_player(t_game *game, int direction)
{
	double	speed;
	double	next_x;
	double	next_y;
	double	side_x;
	double	side_y;

	speed = 0.05 * direction;
	side_x = game->player.dir_y;
	side_y = -game->player.dir_x;
	next_x = game->player.x + side_x * speed;
	next_y = game->player.y + side_y * speed;
	if (game->data->map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
	if (game->data->map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
}
