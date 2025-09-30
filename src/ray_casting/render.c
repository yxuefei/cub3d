/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:02:41 by omalovic          #+#    #+#             */
/*   Updated: 2025/09/11 23:33:52 by alex             ###   ########.fr       */
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

void draw_floor_ceiling(mlx_image_t *img, int y_start, int y_end, uint32_t floor_color, uint32_t ceiling_color)
{
    for (int y = y_start; y < y_end; y++)
    {
        for (int x = 0; x < WIN_WIDTH; x++)
        {
            if (y < WIN_HEIGHT / 2)
                mlx_put_pixel(img, x, y, ceiling_color);
            else
                mlx_put_pixel(img, x, y, floor_color);
        }
    }
}

void render_frame_textured(t_game *game)
{
    // background
    draw_floor_ceiling(game->img, 0, WIN_HEIGHT,
                       game->data->floor_color, game->data->ceiling_color);

    for (int x = 0; x < WIN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)WIN_WIDTH - 1;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

        int map_x = (int)game->player.x;
        int map_y = (int)game->player.y;

        double side_dist_x, side_dist_y;
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
        int step_x, step_y;
        int hit = 0, side = 0;

        if (ray_dir_x < 0)
        { step_x = -1; side_dist_x = (game->player.x - map_x) * delta_dist_x; }
        else { step_x = 1; side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x; }

        if (ray_dir_y < 0)
        { step_y = -1; side_dist_y = (game->player.y - map_y) * delta_dist_y; }
        else { step_y = 1; side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y; }

        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            { side_dist_x += delta_dist_x; map_x += step_x; side = 0; }
            else
            { side_dist_y += delta_dist_y; map_y += step_y; side = 1; }

            if (game->data->map[map_y][map_x] == '1') hit = 1;
        }

        double perp_wall_dist = (side == 0) ?
            (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x :
            (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;

        int line_height = (int)(WIN_HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WIN_HEIGHT / 2;
        if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

        // choose texture
        int tex_num;
        if (side == 0) // X
            tex_num = (ray_dir_x > 0) ? EA : WE;
        else           // Y
            tex_num = (ray_dir_y > 0) ? SO : NO;

        t_tex *tex = &game->tex[tex_num];

        // wall hit coordinate
        double wall_x = (side == 0) ?
            game->player.y + perp_wall_dist * ray_dir_y :
            game->player.x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        int tex_x = (int)(wall_x * (double)tex->width);
        if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
            tex_x = tex->width - tex_x - 1;

        for (int y = draw_start; y < draw_end; y++)
        {
            int d = y * 256 - WIN_HEIGHT * 128 + line_height * 128;
            int tex_y = ((d * tex->height) / line_height) / 256;

            // take pixel from mlx_texture_t
            uint8_t *pix = tex->tex->pixels;
            int idx = (tex_y * tex->width + tex_x) * 4; // RGBA
            uint32_t color = (pix[idx + 0] << 24) | // R
                             (pix[idx + 1] << 16) | // G
                             (pix[idx + 2] << 8)  | // B
                             (pix[idx + 3]);        // A

            if (side) color = (color >> 1) & 0x7F7F7F; // darken the side walls
            mlx_put_pixel(game->img, x, y, color);
        }
    }
}


void render_frame_textured_hook(void *param)
{
    render_frame_textured((t_game *)param);
}

void handle_input_hook(mlx_key_data_t key, void *param)
{
    t_game *game = (t_game *)param;
    double move_speed = 0.1;
    double rot_speed = 0.05;

    if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
    {
        if (game->data->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_x * move_speed)] != '1')
            game->player.x += game->player.dir_x * move_speed;
        if (game->data->map[(int)(game->player.y + game->player.dir_y * move_speed)][(int)(game->player.x)] != '1')
            game->player.y += game->player.dir_y * move_speed;
    }
    else if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
    {
        if (game->data->map[(int)(game->player.y)][(int)(game->player.x - game->player.dir_x * move_speed)] != '1')
            game->player.x -= game->player.dir_x * move_speed;
        if (game->data->map[(int)(game->player.y - game->player.dir_y * move_speed)][(int)(game->player.x)] != '1')
            game->player.y -= game->player.dir_y * move_speed;
    }
    else if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
    {
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
        game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
        game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);
    }
    else if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
    {
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-rot_speed) - game->player.dir_y * sin(-rot_speed);
        game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y * cos(-rot_speed);
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-rot_speed) - game->player.plane_y * sin(-rot_speed);
        game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y * cos(-rot_speed);
    }
    else if (key.key == MLX_KEY_ESCAPE)
        mlx_close_window(game->mlx);
}
