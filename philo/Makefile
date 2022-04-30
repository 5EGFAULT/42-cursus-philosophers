NAME		:= philo
SRC			:= philo.c
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
	./$(NAME) 20 