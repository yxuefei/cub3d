/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:27:42 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/29 16:17:31 by alex             ###   ########.fr       */
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

typedef struct s_tex
{
    mlx_texture_t *tex; // texture loaded from the file
    int width;
    int height;
} t_tex;

enum {
    NO = 0,
    SO = 1,
    WE = 2,
    EA = 3
};

typedef struct s_game
{
    void *mlx;
    t_cub_data *data;
    t_player player;
    mlx_image_t *img;  // image for rendering
    t_tex tex[4];      // textures of walls: 0-NO, 1-SO, 2-WE, 3-EA
	// added
	int win_width;
	int win_height;
} t_game;

typedef struct s_ray
{
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
} t_ray;

typedef struct s_column_params
{
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		side;
	double	perp_wall_dist;
	int		tex_x;
	t_tex	*tex;
}	t_column_params;

typedef struct s_wall_column_params
{
	int			d;
	int			tex_y;
	uint8_t		*pix;
	int			idx;
	uint32_t	color;
}	t_wall_column_params;

// render.c
void load_textures(t_game *game);
// void render_frame_textured_hook(void *param);
void render_frame_textured(t_game *game);

// cub3d_parser.c
// t_cub_data	*parse_cub_file(const char *filename);

// errors:
void	error_general(char *msg);

#endif