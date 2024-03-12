NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
CFLAGS += -g -Og #-fsanitize=address,undefined,leak
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
IFLAGS = -I $(LIBFT_DIR) -I/usr/include -Imlx -Isrc
LFLAGS = -L$(LIBFT_DIR) -lft -Lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LIBMLX = mlx/libmlx_Linux.a
SOURCE_DIR = src
CB_HEADER = $(SOURCE_DIR)/$(NAME).h

include $(LIBFT_DIR)/colors.mk

CB_FILENAMES = \
	app.c \
	error_exit.c

CB_FILENAMES += \
	scene_description/floor_ceiling_validation.c \
	scene_description/map_validation.c \
	scene_description/scene_description.c \
	scene_description/walls_validation.c \
	scene_description/utilities.c

CB_FILENAMES += \
	graphics/graphics.c \
	graphics/mlx_utils.c

CB_FILENAMES += \
	render/render_minimap.c \
	render/render_scene.c

CB_FILENAMES += \
	hooks/key_hooks.c \
	hooks/hooks.c

CB_FILENAMES += \
	game_state/game_state.c

# #TODO: remove
# CB_FILENAMES += \
# 	debug/debug.c

SRC = $(addprefix $(SOURCE_DIR)/,$(CB_FILENAMES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(LIBFT):
	@make -C $(LIBFT_DIR) all clean

#only for testing purposes
dummy: dummy.o  $(LIBFT)
	rm -f dummy
	$(CC) $(CFLAGS) dummy.o -o dummy $(LFLAGS)

lft:
	@make -C $(LIBFT_DIR) all clean

$(LIBMLX):
	cd mlx && ./configure

%.o : %.c $(CB_HEADER)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	bash tests/test_runner.sh

valgrind:
	valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME)

.PHONY: all bonus clean fclean re test lft
