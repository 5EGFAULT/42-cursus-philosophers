NAME		:= philo_bonus
SRC			:= philo_bonus.c ft_atoi_bonus.c utils_bonus.c start_bonus.c eat_bonus.c check_args_bonus.c
OBJ			:= $(patsubst %.c, %.o, $(SRC))
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror -pthread  -g  -fsanitize=thread #-fsanitize=address 
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

bonus:

t: $(NAME)
#	./$(NAME) 1 800 200 200
	./$(NAME) 5 800 200 200
#	./$(NAME) 50 200  100 100
