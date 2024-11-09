CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude

MLX42_LIB = ../MLX42/build/libmlx42.a
LIBS = -L /Users/$(USER)/.brew/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

M_NAME = cub3D
B_NAME = cub3D_bonus

M_SRCS = mandatory/cub.c mandatory/execution/draw.c mandatory/execution/hooks.c mandatory/execution/ray_casting.c mandatory/parsing/error_handle.c mandatory/parsing/get_layout.c \
	mandatory/parsing/get_next_line.c mandatory/parsing/check_textures.c mandatory/parsing/extract_map.c mandatory/parsing/textures.c mandatory/parsing/colors.c \
	mandatory/parsing/map_utils.c mandatory/parsing/gnl_utils.c mandatory/parsing/check_neighbours.c mandatory/execution/ray_casting_utils.c
M_OBJS = $(M_SRCS:.c=.o)

B_SRCS = bonus/cub_bonus.c bonus/execution/draw_bonus.c bonus/execution/hooks_bonus.c bonus/execution/ray_casting_bonus.c bonus/parsing/error_handle_bonus.c \
	bonus/parsing/get_layout_bonus.c bonus/parsing/get_next_line_bonus.c bonus/parsing/check_textures_bonus.c bonus/parsing/extract_map_bonus.c \
	bonus/execution/mini_map_bonus.c bonus/parsing/textures_bonus.c bonus/execution/doors_handler_bonus.c bonus/parsing/frames_bonus.c bonus/parsing/colors_bonus.c \
	bonus/parsing/map_utils_bonus.c bonus/parsing/gnl_utils_bonus.c bonus/parsing/check_neighbours_bonus.c bonus/execution/draw_utils_bonus.c \
	bonus/execution/hooks_utils_bonus.c bonus/execution/ray_casting_utils_bonus.c
B_OBJS = $(B_SRCS:.c=.o)

all: libft_make pre $(M_NAME)

libft_make:
	$(MAKE) -C libft

pre:
	cd ../MLX42 && cmake -B build && cmake --build build

$(M_NAME): $(M_OBJS)
	$(CC) $(CFLAGS) $(M_OBJS) $(MLX42_LIB) libft/libft.a $(LIBS) -o $(M_NAME)

bonus/%.o : bonus/%.c bonus/cub_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

mandatory/%.o: mandatory/%.c mandatory/cub.h
	$(CC) $(CFLAGS)  -c $< -o $@


$(B_NAME): $(B_OBJS)
	$(CC) $(CFLAGS) $(M_OBJS) $(MLX42_LIB) libft/libft.a $(LIBS) -o $(B_NAME)

bonus: libft_make pre $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) $(MLX42_LIB) libft/libft.a $(LIBS) -o $(B_NAME)

clean:
	rm -f $(M_OBJS) $(B_OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(M_NAME) $(B_NAME)
	cd ../MLX42 && rm -rf build
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re pre libft_make