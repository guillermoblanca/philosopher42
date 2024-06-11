NAME = philo

CC := clang
FLAGS := -Wall -Wextra -Werror -g
RM := rm -f
ARGS := 5 800 700 300

HEADER := philosopher.h
SRC := main.c utils.c ft_atoi.c init.c actions.c error.c
OBJ := $(SRC:.c=.o)

%.o: %.c
	@ $(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	@ $(RM) $(OBJ_S) $(OBJ_C)
	@ rm $(OBJ)

fclean: clean
	@ rm $(NAME)
	@ rm $(RM)

re: fclean all

test: re
	@ ./$(NAME) $(ARGS)

.PHONY: all clean fclean re test