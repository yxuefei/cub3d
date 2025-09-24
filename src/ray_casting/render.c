/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:02:41 by omalovic          #+#    #+#             */
/*   Updated: 2025/09/24 15:23:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void load_textures(t_game *game)
{
    char *paths[4] = {
        game->data->no,
        game->data->so,
        game->data->we,
        game->data->ea
    };

    for (int i = 0; i < 4; i++)
    {
        game->tex[i].tex = mlx_load_png(paths[i]);
        if (!game->tex[i].tex)
            error_general("failed to load texture");

        game->tex[i].width  = game->tex[i].tex->width;
        game->tex[i].height = game->tex[i].tex->height;
    }
}

void draw_floor_ceiling(t_game *game, int y_start, int y_end)
{
    for (int y = y_start; y < y_end; y++)
    {
        for (int x = 0; x < WIN_WIDTH; x++)
        {
            if (y < WIN_HEIGHT / 2)
                mlx_put_pixel(game->img, x, y, game->data->ceiling_color);
            else
                mlx_put_pixel(game->img, x, y, game->data->floor_color);
        }
    }
}

void init_ray(t_game *game, int x, t_ray *ray)
{
    double camera_x = 2 * x / (double)WIN_WIDTH - 1;
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

    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
    }

    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
}

int perform_dda(t_game *game, t_ray *ray, int *side)
{
    int hit = 0;

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

    return *side;
}

double calc_wall_distance(t_game *game, t_ray *ray, int side)
{
    double distance;

    if (side == 0)
    {
        distance = (ray->map_x - game->player.x + (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
    }
    else
    {
        distance = (ray->map_y - game->player.y + (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
    }

    return distance;
}

int select_texture(t_ray *ray, int side)
{
    if (side == 0)
    {
        if (ray->ray_dir_x > 0)
            return EA;
        else
            return WE;
    }
    else
    {
        if (ray->ray_dir_y > 0)
            return SO;
        else
            return NO;
    }
}

void draw_wall_column(t_game *game, int x, int draw_start, int draw_end,
                      int tex_x, t_tex *tex, int side, int line_height)
{
    for (int y = draw_start; y < draw_end; y++)
    {
        int d = y * 256 - WIN_HEIGHT * 128 + line_height * 128;
        int tex_y = ((d * tex->height) / line_height) / 256;

        uint8_t *pix = tex->tex->pixels;
        int idx = (tex_y * tex->width + tex_x) * 4;

        uint32_t color = (pix[idx + 0] << 24) |
                         (pix[idx + 1] << 16) |
                         (pix[idx + 2] << 8)  |
                         pix[idx + 3];

        if (side != 0)
            color = (color >> 1) & 0x7F7F7F;

        mlx_put_pixel(game->img, x, y, color);
    }
}

void render_column(t_game *game, int x)
{
    t_ray ray;
    init_ray(game, x, &ray);

    int side;
    perform_dda(game, &ray, &side);

    double perp_wall_dist = calc_wall_distance(game, &ray, side);

    int line_height = (int)(WIN_HEIGHT / perp_wall_dist);
    int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + WIN_HEIGHT / 2;
    if (draw_end >= WIN_HEIGHT)
        draw_end = WIN_HEIGHT - 1;

    int tex_num = select_texture(&ray, side);
    t_tex *tex = &game->tex[tex_num];

    double wall_x;
    if (side == 0)
        wall_x = game->player.y + perp_wall_dist * ray.ray_dir_y;
    else
        wall_x = game->player.x + perp_wall_dist * ray.ray_dir_x;

    wall_x -= floor(wall_x);

    int tex_x = (int)(wall_x * (double)tex->width);
    if ((side == 0 && ray.ray_dir_x > 0) || (side == 1 && ray.ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    draw_wall_column(game, x, draw_start, draw_end, tex_x, tex, side, line_height);
}

void render_frame_textured(t_game *game)
{
    draw_floor_ceiling(game, 0, WIN_HEIGHT);

    for (int x = 0; x < WIN_WIDTH; x++)
        render_column(game, x);
}

void render_frame_textured_hook(void *param)
{
    render_frame_textured((t_game *)param);
}
