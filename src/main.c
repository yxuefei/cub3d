#include "../include/cub.h"

void game_loop(void *param)
{
	t_game *game = (t_game *)param;
	double move_speed = 0.05;
	double rot_speed = 0.03;

	// --- движение ---
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (game->data->map[(int)(game->player.y)]
							[(int)(game->player.x + game->player.dir_x * move_speed)] != '1')
			game->player.x += game->player.dir_x * move_speed;
		if (game->data->map[(int)(game->player.y + game->player.dir_y * move_speed)]
							[(int)(game->player.x)] != '1')
			game->player.y += game->player.dir_y * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (game->data->map[(int)(game->player.y)]
							[(int)(game->player.x - game->player.dir_x * move_speed)] != '1')
			game->player.x -= game->player.dir_x * move_speed;
		if (game->data->map[(int)(game->player.y - game->player.dir_y * move_speed)]
							[(int)(game->player.x)] != '1')
			game->player.y -= game->player.dir_y * move_speed;
	}

	// --- повороты ---
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) // влево
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
		game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);

		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
		game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) // вправо
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot_speed) - game->player.dir_y * sin(-rot_speed);
		game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y * cos(-rot_speed);

		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot_speed) - game->player.plane_y * sin(-rot_speed);
		game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y * cos(-rot_speed);
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);

	// --- рендер ---
	render_frame_textured(game);
}

int main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		printf("Usage: %s map.cub\n", argv[0]);
		return 1;
	}

	game.data = parse_cub_file(argv[1]);
	game.player.x = game.data->player_x + 0.5;
	game.player.y = game.data->player_y + 0.5;
	game.player.dir_x = -1; // смотри на север
	game.player.dir_y = 0;
	game.player.plane_x = 0;
	game.player.plane_y = FOV;

	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", true);
	if (!game.mlx)
		error_general("mlx_init");
	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.mlx)
		error_general("mlx_new_window");
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		error_general("mlx_image_to_window");

	load_textures(&game);

	mlx_loop_hook(game.mlx, game_loop, &game);

	mlx_loop(game.mlx);
	return 0;
}

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         printf("Usage: %s map.cub\n", argv[0]);
//         return 1;
//     }

//     t_cub_data *data = parse_cub_file(argv[1]);
//     t_player player;
//     player.x = data->player_x + 0.5;
//     player.y = data->player_y + 0.5;
//     player.dir_x = -1; // смотри на север
//     player.dir_y = 0;
//     player.plane_x = 0;
//     player.plane_y = FOV;

//     void *mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", 1);
//     mlx_image_t *img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);

//     render_frame(data, &player, img);
//     mlx_image_to_window(mlx, img, 0, 0);
//     mlx_loop(mlx);

//     return 0;
// }