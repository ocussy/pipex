NAME = pipex
SRC_FILES = main.c \
            
OBJECTS = $(patsubst %.c, %.o, $(SRC_FILES))
INCLUDE = pipex.h
CC = cc 
FLAGS = -Wall -Wextra -Werror -O3 -g3
LIBFT_PATH = libft/
FT_PRINTF_PATH = ft_printf/
FT_PRINTF = $(FT_PRINTF_PATH)libftprintf.a
LIBFT = $(LIBFT_PATH)libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
