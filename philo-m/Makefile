NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = philo.c utils.c utils_2.c start_table.c philo_condition.c  philo_action.c

OBJ_SRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ_SRC)
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ_SRC)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclea re
