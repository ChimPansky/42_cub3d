NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
CFLAGS += -g -Og #-fsanitize=address,undefined,leak
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
IFLAGS = -I $(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft #TODO: add mlx stuff
SOURCE_DIR = src
CB_HEADER = $(SOURCE_DIR)/$(NAME).h

include $(LIBFT_DIR)/colors.mk

CB_FILENAMES = \
	cub3d.c \
	destroy.c \
	error_exit.c \
	scene_validation.c \
	# app.c

SRC = $(addprefix $(SOURCE_DIR)/,$(CB_FILENAMES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
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
