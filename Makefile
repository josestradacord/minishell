# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 18:48:41 by joestrad          #+#    #+#              #
#    Updated: 2024/02/07 17:52:12 by joestrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c init_checks.c environment.c list_env.c parser.c builtins.c executor.c clean_free.c

CC = gcc

#42
#LIB_READLINE = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib 

#INC_READLINE = -I/Users/$(USER)/.brew/opt/readline/include

#Home
LIB_READLINE = -lreadline -L/usr/local/opt/readline/lib 

INC_READLINE = -I/usr/local/opt/readline/include

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
	@$(CC) -c $(FLAGS) $< -o $@ $(INC_READLINE)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo $(YELLOW)minishell norminette...$(NOCOLOR)
#	@norminette $(SRCS)
	@echo $(GREEN)Compiling minishell...$(NOCOLOR)
	@$(CC) $(INC_READLINE) $(LIB_READLINE) $(FLAGS) $(INC) $(LIBFT) $(SRCS) -o $(NAME)
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

.PHONY: all clean fclean re
