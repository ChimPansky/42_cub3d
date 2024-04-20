NAME = cub3d
all: $(NAME)

LIBMLX = mlx/libmlx_Linux.a
$(LIBMLX):
	cd mlx && ./configure

include libft/colors.mk
LIBFT = libft/libft.a
$(LIBFT):
	@make -C libft all clean

lft:
	@make -C libft all clean

.PHONY: lft

CC = cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
CFLAGS += -g -Og #-fsanitize=address,undefined,leak
# CFLAGS += -O3
IFLAGS = -I/usr/include -Ilibft -Imlx -Isrc
LFLAGS = -Llibft -lft -Lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
SOURCE_DIR = src

CB_FILENAMES = \
	cub3d.c \
	utils.c

CB_FILENAMES += \
	hooks/key_hooks.c \
	hooks/hooks.c

CB_FILENAMES += \
	logic/logic.c

CB_FILENAMES += \
	render/render_minimap.c \
	render/render_scene.c

CB_FILENAMES += \
	input_parsing/input_parsing.c \
	input_parsing/parse_floor_ceiling_colors.c \
	input_parsing/parse_map.c \
	input_parsing/parse_wall_textures.c \
	input_parsing/prepare_map.c \
	input_parsing/utilities.c

CB_FILENAMES += \
	structs/app.c \
	structs/door.c \
	structs/game_state.c \
	structs/graphics.c \
	structs/image.c \
	structs/inputs.c \
	structs/map.c \
	structs/minimap.c \
	structs/physics.c \
	structs/player.c \
	structs/ray.c \
	structs/ray2.c \
	structs/sprites.c \
	structs/trgb.c \

CB_FILENAMES += \
	vector/vector_cartesian.c \
	vector/vector_cartesian2.c \
	vector/vector_polar.c \
	vector/vector_utilities.c

SRC = $(addprefix $(SOURCE_DIR)/,$(CB_FILENAMES))

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

%.o : %.c $(CB_HEADER)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME) cub_files/valid/01_subject_map_random_pix.cub

.PHONY: all bonus clean fclean re test
