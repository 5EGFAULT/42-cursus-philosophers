NAME		:= philo
SRC			:= philo.c ft_atoi.c utils.c start.c eat.c check_args.c
OBJ			:= $(patsubst %.c, %.o, $(SRC))
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror -pthread  -g  #-fsanitize=address
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
