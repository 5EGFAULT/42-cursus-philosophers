NAME		:= philo_bonus
SRC			:= utils_bonus.c init_bonus.c start_bonus.c philo_bonus.c check_args_bonus.c eat_bonus.c
OBJ			:= $(patsubst %.c, %.o, $(SRC))
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror  -pthread 
.PHONY: all clean fclean re bonus

all: $(NAME)
$(NAME): $(OBJ)
	@$(CC)  $(FLAGS)  $(OBJ) -o $(NAME) 
%.o: %.c
	$(CC) $(FLAGS) -c $<  -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all