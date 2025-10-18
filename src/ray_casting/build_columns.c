/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_columns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:27:37 by omalovic          #+#    #+#             */
/*   Updated: 2025/10/18 15:28:57 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_ray(t_game *game, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->win_width - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	set_ray_steps(game, ray);
}

static void	calc_column_params(t_game *game, int x,
				t_ray *ray, t_column_params *params)
{
	init_ray(game, x, ray);
	perform_dda(game, ray, &params->side);
	params->perp_wall_dist = calc_wall_distance(game, ray, params->side);
	params->line_height = (int)(game->win_height / params->perp_wall_dist);
	params->draw_start = -params->line_height / 2 + game->win_height / 2;
	if (params->draw_start < 0)
		params->draw_start = 0;
	params->draw_end = params->line_height / 2 + game->win_height / 2;
	if (params->draw_end >= game->win_height)
		params->draw_end = game->win_height - 1;
}

void	draw_wall_column(t_game *game, int x, t_column_params *params)
{
	t_wall_column_params	column_params;
	int						y;

	y = params->draw_start;
	while (y < params->draw_end)
	{
		column_params.d = y * 256 - game->win_height * 128
			+ params->line_height * 128;
		column_params.tex_y = ((column_params.d
					* params->tex->height) / params->line_height) / 256;
		column_params.pix = params->tex->tex->pixels;
		column_params.idx = (column_params.tex_y
				* params->tex->width + params->tex_x) * 4;
		column_params.color = (column_params.pix[column_params.idx + 0] << 24)
			| (column_params.pix[column_params.idx + 1] << 16)
			| (column_params.pix[column_params.idx + 2] << 8)
			| column_params.pix[column_params.idx + 3];
		if (params->side != 0)
			column_params.color = (column_params.color >> 1) & 0x7F7F7F;
		mlx_put_pixel(game->img, x, y, column_params.color);
		y++;
	}
}

static void	render_column_texture(t_game *game, int x,
				t_ray *ray, t_column_params *params)
{
	int		tex_num;
	double	wall_x;

	tex_num = select_texture(ray, params->side);
	params->tex = &game->tex[tex_num];
	if (params->side == 0)
		wall_x = game->player.y + params->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + params->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	params->tex_x = (int)(wall_x * (double)params->tex->width);
	if ((params->side == 0 && ray->ray_dir_x > 0)
		|| (params->side == 1 && ray->ray_dir_y < 0))
		params->tex_x = params->tex->width - params->tex_x - 1;
	draw_wall_column(game, x, params);
}

void	render_column(t_game *game, int x)
{
	t_ray			ray;
	t_column_params	params;

	calc_column_params(game, x, &ray, &params);
	render_column_texture(game, x, &ray, &params);
}
