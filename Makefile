NAME = cub3D

all: $(NAME)

SOURCE_DIR = src
BUILD_DIR = build

CC = cc
CFLAGS = -Wall -Werror -Wextra -Wpedantic
CFLAGS += -g -Og #-fsanitize=address,undefined,leak

IFLAGS = -I/usr/include -I$(SOURCE_DIR)
LFLAGS = -lm

LIBMLX = libs/mlx/libmlx_Linux.a
$(LIBMLX):
	cd libs/mlx && ./configure
IFLAGS += -Ilibs/mlx
LFLAGS += -Llibs/mlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lz

include libs/libft/colors.mk
LIBFT = libs/libft/libft.a
$(LIBFT):
	@make -C libs/libft all clean
IFLAGS += -Ilibs/libft
LFLAGS += -Llibs/libft -lft

.PHONY: lft
lft:
	@make -C libs/libft all clean

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
	input_parsing/parse_doors.c \
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
	structs/image_to_image_transformed.c \
	structs/inputs.c \
	structs/map.c \
	structs/minimap.c \
	structs/physics.c \
	structs/player.c \
	structs/ray.c \
	structs/ray2.c \
	structs/sprites.c \
	structs/trgb.c

CB_FILENAMES += \
	vector/vector_cartesian.c \
	vector/vector_cartesian2.c \
	vector/vector_polar.c \
	vector/vector_utilities.c

SRC = $(addprefix $(SOURCE_DIR)/,$(CB_FILENAMES))
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(BUILD_DIR)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -MMD -c $< -o $@

-include $(DEP)

clean:
	rm -fr $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME) cub_files/valid/01_subject_map_random_pix.cub

.PHONY: all bonus clean fclean re test
