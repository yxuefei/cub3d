#include "../include/cub.h"

void game_loop(void *param)
{
	t_game *game = (t_game *)param;
	double move_speed = 0.05;
	double rot_speed = 0.03;

	// Moves of the player clicking on the buttoms
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

	// Turns
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) // left
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
		game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);

		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
		game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) // right
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

	// render
	render_frame_textured(game);
}

// int main(int argc, char **argv)
// {
// 	t_game game;

// 	if (argc != 2)
// 	{
// 		printf("Usage: %s map.cub\n", argv[0]);
// 		return 1;
// 	}

// 	game.data = parse_cub_file(argv[1]);
// 	game.player.x = game.data->player_x + 0.5;
// 	game.player.y = game.data->player_y + 0.5;
// 	game.player.dir_x = -1; // look at the North
// 	game.player.dir_y = 0;
// 	game.player.plane_x = 0;
// 	game.player.plane_y = FOV;

// 	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", true);
// 	if (!game.mlx)
// 		error_general("mlx_init");
// 	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
// 	if (!game.mlx)
// 		error_general("mlx_new_window");
// 	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
// 		error_general("mlx_image_to_window");

// 	load_textures(&game);

// 	mlx_loop_hook(game.mlx, game_loop, &game);

// 	mlx_loop(game.mlx);
// 	return 0;
// }

//parsing test main
int	main(int argc, char **argv)
{
	t_cub_data	*d;
	int			i;
	t_game		game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	d = parse_cub_file(&game, argv[1]);
	if (!d)
	{
		printf("Error: parsing failed.\n");
		return (1);
	}
	printf("NO: %s\n", d->no);
	printf("SO: %s\n", d->so);
	printf("WE: %s\n", d->we);
	printf("EA: %s\n", d->ea);
	printf("Floor: 0x%06X\n", d->floor_color);
	printf("Ceiling: 0x%06X\n", d->ceiling_color);
	printf("Player: (%d,%d) dir=%c\n",
		d->player_x, d->player_y, d->player_dir);
	printf("Map:\n");
	i = 0;
	while (d->map && d->map[i])
	{
		printf("%s\n", d->map[i]);
		i++;
	}
	free_data(d);
	free(d);
	return (0);
}
