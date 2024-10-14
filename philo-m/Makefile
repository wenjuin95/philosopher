NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = philo.c utils.c utils_2.c start_table.c philo_condition.c  philo_action.c

OBJ_FOLDER = object_files

OBJ_SRC = $(SRC:%.c=$(OBJ_FOLDER)/%.o)

# color
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME) : $(OBJ_SRC)
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $@
	@echo "${GREEN}-----COMPILED DONE-----\n${RESET}"


$(OBJ_FOLDER)/%.o : %.c | $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

clean :
	rm -f $(OBJ_FOLDER)

fclean : clean
	rm -f $(NAME)
	@echo "${GREEN}-----FULLY REMOVE-----\n${RESET}"

re : fclean all

norm :
	@echo "${GREEN}-----CHECKING ALL FILES-----${RESET}"
	@norminette philo.c utils.c utils_2.c start_table.c philo_condition.c  philo_action.c philo.h

check_eat :
	@bash check_eat.sh

.PHONY : all clean fclea re
