NAME = minishell

SRCS = minishell.c checks.c environment.c list_env.c parser.c builtins.c

CC = gcc

READLINE = -lreadline

FLAGS = -Wall -Werror -Wextra 

RM = rm -f

OBJS = $(SRCS:.c=.o)

INC_LFT = -I libft
LIBFT = libft/libft.a

INC = -I include $(INC_LFT)

GREEN = "\033[32m"
YELLOW = "\033[33m"
RED = "\033[31m"
NOCOLOR = "\033[0m"

%.o: %.c
	@$(CC) -c $(FLAGS) $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo $(YELLOW)minishell norminette...$(NOCOLOR)
#	@norminette $(SRCS)
	@echo $(GREEN)Compiling minishell...$(NOCOLOR)
	@$(CC) $(FLAGS) $(INC) $(LIBFT) $(SRCS) -o $(NAME) $(READLINE)
	@echo $(GREEN)Program minishell ready$(NOCOLOR)

$(LIBFT):
	@echo $(YELLOW)Compiling libft$(NOCOLOR)
	@make -C libft --silent
	@make bonus -C libft --silent

clean:
	@$(RM) $(OBJS)
	@make clean -C libft --silent
	@echo minishell objects files $(RED)cleaned$(NOCOLOR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo minishell executables files $(RED)cleaned$(NOCOLOR)

re: fclean all
	@echo $(RED)Cleaned$(NOCOLOR) and $(GREEN)rebuilt$(NOCOLOR) minishell project
