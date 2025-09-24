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

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		rotate_player(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		rotate_player(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
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
	game.player.dir_x = -1; // look at the North
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
