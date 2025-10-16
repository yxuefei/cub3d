CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = cub3d

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c src/moving_player.c src/ray_casting/render.c src/ray_casting/build_columns.c src/ray_casting/utils.c src/parsing/check_border_utils.c src/parsing/check_border.c src/parsing/check_element.c src/parsing/check_file.c src/parsing/check_map_is_last.c src/parsing/check_map.c src/parsing/check_player_start.c src/parsing/check_texture.c src/parsing/create_game_map.c src/parsing/fill_color_texture.c src/parsing/get_file_data.c src/parsing/get_file_data2.c src/parsing/init_data_and_utils.c src/parsing/load_cub_file.c src/parsing/map_access.c src/parsing/parser_cub_file.c src/parsing/parsing_utils.c src/parsing/parsing.c
OBJS = $(SRCS:.c=.o)

MLX_DIR := ./MLX42
MLX_LIB := $(MLX_DIR)/build/libmlx42.a
LDFLAGS = -L/opt/homebrew/lib -lglfw
# LIBS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBS := -lglfw -lX11 -lXext -lm -ldl -lpthread


all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)/build/libmlx42.a
	rm -rf tester
re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -I./MLX42/include -I$(LIBFT_DIR) -c $< -o $@

.PHONY: all clean fclean re
