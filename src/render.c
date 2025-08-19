#include "../include/cub.h"

static void draw_vertical_line(mlx_image_t *img, int x, int y_start, int y_end, int color)
{
	int y;

	y = y_start;
	while (y < y_end)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void render_frame(t_cub_data *data, t_player *player, mlx_image_t *img)
{
    int x;
    for (x = 0; x < WIN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)WIN_WIDTH - 1;
        double ray_dir_x = player->dir_x + player->plane_x * camera_x;
        double ray_dir_y = player->dir_y + player->plane_y * camera_x;

        int map_x = (int)player->x;
        int map_y = (int)player->y;

        double side_dist_x, side_dist_y;
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
        int step_x, step_y;
        int hit = 0, side;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (player->x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (player->y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
        }

        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (data->map[map_y][map_x] == '1')
                hit = 1;
        }

        double perp_wall_dist = (side == 0) ?
            (map_x - player->x + (1 - step_x) / 2) / ray_dir_x :
            (map_y - player->y + (1 - step_y) / 2) / ray_dir_y;

        int line_height = (int)(WIN_HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WIN_HEIGHT / 2;
        if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

        uint32_t color = 0xFFFFFF; // пока белые стены
        if (side == 1) color = 0xAAAAAA; // тень для боковой стены

        draw_vertical_line(img, x, draw_start, draw_end, color);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s map.cub\n", argv[0]);
        return 1;
    }

    t_cub_data *data = parse_cub_file(argv[1]);
    t_player player;
    player.x = data->player_x + 0.5;
    player.y = data->player_y + 0.5;
    player.dir_x = -1; // смотри на север
    player.dir_y = 0;
    player.plane_x = 0;
    player.plane_y = FOV;

    void *mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", 1);
    mlx_image_t *img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);

    render_frame(data, &player, img);
    mlx_image_to_window(mlx, img, 0, 0);
    mlx_loop(mlx);

    return 0;
}