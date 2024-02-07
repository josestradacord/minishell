RM = rm -f

CC = gcc
#CCFLAGS = -Wall -Wextra -Werror

NAME = pipex
SRC = main_bonus.c commands_bonus.c utils_bonus.c input_bonus.c

OBJ = $(SRC:.c=.o)

LIBFT = ./../libft

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	$(CC) $(OBJ) $(LIBFT)/libft.a -o $(NAME)
	

clean:
	make -C $(LIBFT) clean
	$(RM) $(OBJ) 

fclean:
	make -C $(LIBFT) fclean
	$(RM) $(OBJ) $(NAME)

re: fclean all