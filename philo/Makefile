NAME		:= philo
SRC			:= utils.c init.c start.c philo.c check_args.c eat.c
OBJ			:= $(patsubst %.c, %.o, $(SRC))
CC			:= gcc
#FLAGS		:= -Wall -Wextra -Werror -pthread  -g   -fsanitize=thread 
FLAGS		:= -Wall -Wextra -Werror -pthread  -g    #-fsanitize=address
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

1: $(NAME)
	./$(NAME) 5 800 200 200
2: $(NAME)
	./$(NAME) 2 800 200 200
3: $(NAME)
	./$(NAME) 3 800 200 200
4: $(NAME)
	./$(NAME) 4 800 200 200