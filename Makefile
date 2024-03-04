# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 18:48:41 by joestrad          #+#    #+#              #
#    Updated: 2024/02/11 16:05:06 by gpaez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJ_DIR = ./obj
SRC_DIR = ./srcs

SRCS = $(wildcard $(SRC_DIR)/*.c)
CC = gcc

LIB_READLINE = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib 

#GLFW_FLAGS  = -ldl -lglfw -lm
#GLFW_FLAGS = -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ -lm

INC_READLINE = -I/Users/$(USER)/.brew/opt/readline/include

FLAGS = -Wall -Werror -Wextra 

RM = rm -f

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

INC_LFT = -I libft
LIBFT = libft/libft.a

INC = -I include $(INC_LFT)

GREEN = "\033[32m"
YELLOW = "\033[33m"
RED = "\033[31m"
NOCOLOR = "\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(FLAGS) $< -o $@ $(INC_READLINE)

all: $(NAME)


$(NAME): $(LIBFT) $(OBJS)
	@echo $(YELLOW)minishell norminette...$(NOCOLOR)
#	@norminette $(SRCS)
	@echo $(GREEN)Compiling minishell...$(NOCOLOR)
	@$(CC) $(FLAGS) $(OBJS) $(INC) $(LIBFT) -o $(NAME) $(INC_READLINE) $(LIB_READLINE)
	@echo $(GREEN)Program minishell ready$(NOCOLOR)

$(LIBFT):
	@echo $(YELLOW)Compiling libft$(NOCOLOR)
	@make -C libft --silent
	@make bonus -C libft --silent

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	@make clean -C libft --silent
	@echo minishell objects files $(RED)cleaned$(NOCOLOR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo minishell executables files $(RED)cleaned$(NOCOLOR)

re: fclean all
	@echo $(RED)Cleaned$(NOCOLOR) and $(GREEN)rebuilt$(NOCOLOR) minishell project

.PHONY: all clean fclean re