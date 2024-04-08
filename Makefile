NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = philo.c utils.c init.c philo_action.c 

BONUS = 

OBJ_SRC = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ_SRC)
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ_SRC)
	rm -f $(OBJ_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all

bonus: $(OBJ_BONUS) 
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)

.PHONY : all clean fclea re
