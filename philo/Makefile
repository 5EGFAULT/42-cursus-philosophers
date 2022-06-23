NAME		:= philo
SRC			:= utils.c init.c start.c philo.c check_args.c eat.c
OBJ			:= $(patsubst %.c, %.o, $(SRC))
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror -pthread
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
