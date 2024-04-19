NAME = pipex
NAME_BONUS = pipex_bonus
SRC_FILES = find_path.c \
			make_struct.c \
			pipex_mandatory.c \
			pipex.c \
			utils.c \
			utils_2.c \

SRC_BONUS = find_path.c \
			make_struct.c \
			pipex_bonus.c \
			pipex.c \
			utils.c \
			utils_2.c \
			utils_bonus.c \
            
OBJECTS = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS_BONUS = $(patsubst %.c, %.o, $(SRC_BONUS))
INCLUDE = pipex.h
CC = cc 
FLAGS = -Wall -Wextra -Werror -O3 -g3
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJECTS_BONUS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJECTS_BONUS) $(LIBFT) -o $(NAME_BONUS)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
