#include "../include/cub.h"

void rotate_player(t_game *game, int direction)
{
	double	angle;
	double	cos_a;
	double	sin_a;
	double	tmp;

	angle = 0.03 * direction;
	cos_a = cos(angle);
	sin_a = sin(angle);
	tmp = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = tmp * sin_a + game->player.dir_y * cos_a;
	tmp = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = tmp * sin_a + game->player.plane_y * cos_a;
}

void move_player(t_game *game, int direction)
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

void strafe_player(t_game *game, int direction)
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

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		strafe_player(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		strafe_player(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	render_frame_textured(game);
}

void	handle_resize(int new_width, int new_height, void *param)
{
	t_game *game = (t_game *)param;

	game->win_height = new_height;
	game->win_width = new_width;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	if (!game->img)
		error_general("Failed to create a new image");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_general("mlx_image_to_window");
}

void	cleanup(t_game *game)
{
	int	i;

	if (!game)
		return;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	i = 0;
	while (i < 4)
	{
		if (game->tex[i].tex)
			mlx_delete_texture(game->tex[i].tex);
		i++;
	}
	if (game->data)
	{
		free_data(game->data);
		free(game->data);
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
}

int main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}

	game.data = parse_cub_file(&game, argv[1]);
	if (!game.data)
		exit(EXIT_FAILURE);
	game.player.x = game.data->player_x + 0.5;
	game.player.y = game.data->player_y + 0.5;
	game.player.dir_x = -1; // look at the North
	game.player.dir_y = 0;
	game.player.plane_x = 0;
	game.player.plane_y = FOV;

	game.win_height = WIN_HEIGHT;
	game.win_width = WIN_WIDTH;
	game.mlx = mlx_init(game.win_width, game.win_height, "Cub3D", true);
	if (!game.mlx)
		error_general("mlx_init");
	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.img)
		error_general("mlx_new_window");
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		error_general("mlx_image_to_window");

	load_textures(&game);

	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_resize_hook(game.mlx, handle_resize, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return 0;
}
