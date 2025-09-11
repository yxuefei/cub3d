CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = cub3d

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c src/ray_casting/render.c src/cub3d_parser.c src/utils/error_handling.c
OBJS = $(SRCS:.c=.o)

MLX_DIR := ./MLX42
MLX_LIB := $(MLX_DIR)/build/libmlx42.a
# LIBS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBS := -lglfw -lX11 -lXext -lm -ldl -lpthread

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)

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
re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -I./MLX42/include -I$(LIBFT_DIR) -c $< -o $@

.PHONY: all clean fclean re
