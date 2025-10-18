/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:27:42 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/18 15:41:14 by omalovic         ###   ########.fr       */
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
# include "../MLX42/include/MLX42/MLX42.h"

# define MAX_ROW	1024
# define IMG_WIDTH	64
# define IMG_HEIGHT 64
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 0.66 // field of view

/* path */
# include "../libft/get_next_line.h"

typedef struct s_cub_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
	void	*mlx;
	void	*win;
}	t_cub_data;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_tex
{
	mlx_texture_t	*tex;
	int				width;
	int				height;
}	t_tex;

enum
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

typedef struct s_game
{
	void		*mlx;
	t_cub_data	*data;
	t_player	player;
	mlx_image_t	*img;
	t_tex		tex[4];
	int			win_width;
	int			win_height;
}	t_game;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
}	t_ray;

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

// moving_player.c
void		rotate_player(t_game *game, int direction);
void		move_player(t_game *game, int direction);
void		strafe_player(t_game *game, int direction);

// render.c
void		render_frame_textured(t_game *game);
void		set_ray_steps(t_game *game, t_ray *ray);
int			perform_dda(t_game *game, t_ray *ray, int *side);
double		calc_wall_distance(t_game *game, t_ray *ray, int side);

// utils.c:
void		error_general(char *msg);
uint32_t	color_to_rgba(uint32_t color);
void		load_textures(t_game *game);
int			select_texture(t_ray *ray, int side);

// build_columns.c
void		render_column(t_game *game, int x);

// parsing
int			get_map_height(char **map);
int			validate_map(t_cub_data *d);
int			check_borders(char **map, int height);
int			check_map_elements(t_cub_data *d);
int			fix_and_validate_player_pos(t_cub_data *d);
int			check_map_is_last(char **lines, int map_end);
int			parse_scene(char **lines, t_cub_data *d);
int			parse_color_string(const char *s);
char		*parse_texture_path(const char *s);
void		free_lines(char **lines);
int			load_cub_file(const char *path, char ***lines);
int			check_file(char *arg);
int			load_and_parse(char *path, t_cub_data *d);
int			validate_textures(t_cub_data *d);
int			set_floor_color_from_line(t_cub_data *d, const char *line);
int			set_ceiling_color_from_line(t_cub_data *d, const char *line);
int			find_map_range(char **lines, int *start, int *end);
char		**create_game_map(char **lines, int start, int end);
int			check_open_tiles_closed(char **map);
void		init_data(t_cub_data *d);
t_cub_data	*parse_cub_file(t_game *g, char *filename);
void		free_data(t_cub_data *d);
char		map_at(t_cub_data *d, int x, int y);
int			map_is_wall(t_cub_data *d, double x, double y);
int			is_blank(char c);
int			first_noblank_idx(char *s);
int			last_noblank_idx(char *s);
int			row_len_upto_nl(char *s);
int			starts_with_id(const char *s, const char *id);
int			is_map_line(const char *s);
int			is_nonblank_line(const char *s);
void		skip_ws(const char *s, int *i);
const char	*after_id_ptr(const char *line, const char *id);
int			parse_header_line(t_cub_data *d, const char *line);
bool		is_png_file(char *arg);

#endif