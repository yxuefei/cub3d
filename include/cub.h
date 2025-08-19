/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:27:42 by xueyang           #+#    #+#             */
/*   Updated: 2025/08/19 16:31:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
// # include "./MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define MAX_ROW	1024
// # define MAX_COL	100
# define IMG_WIDTH	64
# define IMG_HEIGHT 64
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 0.66 // field of view

/* path */
# include "../libft/get_next_line.h"

# define PNG_PLAYER		"./assets/player2.png"
# define PNG_COLLECT	"./assets/collect.png"
# define PNG_EXIT		"./assets/exit.png"
# define PNG_WALL		"./assets/wall1.png"
# define PNG_FLOOR		"./assets/floor.png"

# define ENEMY1		"./assets/enemy1.png"
# define ENEMY2		"./assets/enemy2.png"
# define ENEMY3		"./assets/enemy3.png"
# define ENEMY4		"./assets/enemy4.png"
# define ENEMY5		"./assets/enemy5.png"

# define WALL		'1'
# define FLOOR		'0'
# define PLAYER		'P'
# define EXIT		'E'
# define COLLECT	'C'

typedef struct s_img
{
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;
	mlx_image_t	*exit_img;
	mlx_image_t	*player_img;
	mlx_image_t	*collect_img;
}				t_img;

typedef struct s_map
{
	int	columns;
	int	rows;
	int	collect_num;
	int	player_num;
	int	exit_num;
}		t_map;

// typedef struct s_player
// {
// 	int	x;
// 	int	y;
// 	int	move;
// }		t_player;

typedef struct s_enemy
{
	mlx_image_t	*frames[5];
	int			cur;
	int			delay;
	int			move;
	int			x;
	int			y;
}				t_enemy;

typedef struct s_cub_data
{
	char *no;
	char *so;
	char *we;
	char *ea;
	int  floor_color;
	int  ceiling_color;
	char **map;
	// int map_rows;
	// int map_cols;
	int player_x;
	int player_y;
	char player_dir;
	void *mlx;
	void *win;
} t_cub_data;

typedef struct s_player
{
	double x, y;
	double dir_x, dir_y;
	double plane_x, plane_y;
} t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	int			fd;
	t_img		*img;
	t_map		*map;
	t_player	*player;
	t_enemy		*enemy;
	int			count;
	int			finish_game;
	int			reach_collect;
	int			reach_exit;
	char		**real_map;
}				t_game;

// render.c
void		render_frame(t_cub_data *data, t_player *player, mlx_image_t *img);

// cub3d_parser.c
t_cub_data	*parse_cub_file(const char *filename);

void		check_map(t_game *game, char **map);
void		free_array(char **arr);
void		is_valid_map(t_game *game, char **map, int p_x, int p_y);
void		read_map(t_game *game, char *filename);
void		place_img(t_game *game, char **map);
void		put_image(t_game *game, int i, int j, mlx_image_t *img);
void		key_event_up(t_game *game);
void		key_event_down(t_game *game);
void		key_event_left(t_game *game);
void		key_event_right(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
void		finish_game(t_game *game);
mlx_image_t	*process_png(char *path, t_game *game);
t_img		*init_img(t_game *game);
void		init_mlx(t_game *game);
t_map		*init_map(t_game *game);
t_player	*init_player(t_game *game);
t_game		*init_game(char **av);
void		error_general(char *msg);
void		error_read_map(char *msg, t_game *game);
void		error_free_map(char *msg, t_game *game);
void		error_free_all(char *msg, t_game *game);
void		normal_exit(char *msg, t_game *game);
t_enemy		*init_enemy(t_game *game);

#endif