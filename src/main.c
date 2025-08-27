#include "../include/cub.h"


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
    game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);

    load_textures(&game);

    // обёртки для MLX42
    mlx_loop_hook(game.mlx, render_frame_textured_hook, &game);
    mlx_key_hook(game.mlx, handle_input_hook, &game);

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