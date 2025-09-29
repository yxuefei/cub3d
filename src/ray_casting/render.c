/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:02:41 by omalovic          #+#    #+#             */
/*   Updated: 2025/09/29 16:26:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	load_textures(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = game->data->no;
	paths[1] = game->data->so;
	paths[2] = game->data->we;
	paths[3] = game->data->ea;
	i = 0;
	while (i < 4)
	{
		game->tex[i].tex = mlx_load_png(paths[i]);
		if (!game->tex[i].tex)
			error_general("failed to load texture");
		game->tex[i].width = game->tex[i].tex->width;
		game->tex[i].height = game->tex[i].tex->height;
		i++;
	}
}

void	draw_floor_ceiling(t_game *game, int y_start, int y_end)
{
	int	y;
	int	x;

	y = y_start;
	while (y < y_end)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->data->ceiling_color);
			else
				mlx_put_pixel(game->img, x, y, game->data->floor_color);
			x++;
		}
		y++;
	}
}

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

void	init_ray(t_game *game, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
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

int	select_texture(t_ray *ray, int side)
{
	if (side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SO);
		else
			return (NO);
	}
}

static void	calc_column_params(t_game *game, int x,
				t_ray *ray, t_column_params *params)
{
	init_ray(game, x, ray);
	perform_dda(game, ray, &params->side);
	params->perp_wall_dist = calc_wall_distance(game, ray, params->side);
	params->line_height = (int)(WIN_HEIGHT / params->perp_wall_dist);
	params->draw_start = -params->line_height / 2 + WIN_HEIGHT / 2;
	if (params->draw_start < 0)
		params->draw_start = 0;
	params->draw_end = params->line_height / 2 + WIN_HEIGHT / 2;
	if (params->draw_end >= WIN_HEIGHT)
		params->draw_end = WIN_HEIGHT - 1;
}

void	draw_wall_column(t_game *game, int x, t_column_params *params)
{
	t_wall_column_params	column_params;
	int						y;

	y = params->draw_start;
	while (y < params->draw_end)
	{
		column_params.d = y * 256 - WIN_HEIGHT * 128
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

void	render_frame_textured(t_game *game)
{
	int	x;

	draw_floor_ceiling(game, 0, WIN_HEIGHT);
	x = 0;
	while (x < WIN_WIDTH)
	{
		render_column(game, x);
		x++;
	}
}
