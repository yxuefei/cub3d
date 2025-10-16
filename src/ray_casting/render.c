/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:02:41 by omalovic          #+#    #+#             */
/*   Updated: 2025/10/16 13:36:15 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	set_ray_steps(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0
				- game->player.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0
				- game->player.y) * ray->delta_dist_y;
	}
}

int	perform_dda(t_game *game, t_ray *ray, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			*side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			*side = 1;
		}
		if (game->data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (*side);
}

double	calc_wall_distance(t_game *game, t_ray *ray, int side)
{
	double	distance;

	if (side == 0)
		distance = (ray->map_x - game->player.x
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		distance = (ray->map_y - game->player.y
				+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
	return (distance);
}

void	draw_floor_ceiling(t_game *game, int y_start, int y_end)
{
	int	y;
	int	x;

	y = y_start;
	while (y < y_end)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				mlx_put_pixel(game->img, x, y, game->data->ceiling_color);
			else
				mlx_put_pixel(game->img, x, y, game->data->floor_color);
			x++;
		}
		y++;
	}
}

void	render_frame_textured(t_game *game)
{
	int	x;

	draw_floor_ceiling(game, 0, game->win_height);
	x = 0;
	while (x < game->win_width)
	{
		render_column(game, x);
		x++;
	}
}
