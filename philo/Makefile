NAME = philo

CC := clang
FLAGS := -Wall -Wextra -Werror -g -pthread
RM := rm -f
ARGS := 5 1000 300 200 2

HEADER := philosopher.h
SRC := main.c utils.c ft_atoi.c init.c actions.c error.c time.c eat.c
OBJ := $(SRC:.c=.o)
OBJ_DIR := obj/

GREEN_C := "\033[0;32m"
RED_C := "\033[0;31m"
RESET_C := "\033[0m"

$(shell mkdir -p $(OBJ_DIR))

$(OBJ_DIR)%.o: %.c
	@ $(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ))
	@ $(CC) $(FLAGS) -o $(NAME) $(addprefix $(OBJ_DIR),$(OBJ))
	@echo $(GREEN_C)"Compiled!"$(RESET_C)

clean:
	@ $(RM) $(OBJ_DIR)*.o

fclean: clean
	@ $(RM) $(NAME)
	@ echo $(RED_C)"Cleaned and removed executable"$(RESET_C)

re: fclean all
	@ echo $(GREEN_C)Rebuilded!$(RESET_C)
test: re
	@ ./$(NAME) $(ARGS)

.PHONY: all clean fclean re test