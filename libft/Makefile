# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 16:28:03 by joestrad          #+#    #+#              #
#    Updated: 2024/02/09 12:30:12 by gpaez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c\
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c\
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c\
	   ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
	   ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
	   ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	   ft_printf.c ft_putchar_len.c ft_putnbr_len.c ft_putnbru_len.c\
	   ft_putstr_len.c ft_puthexa_len.c ft_putptr_len.c\
	   get_next_line.c

BSRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
		ft_lstmap_bonus.c

RM = rm -f

OBJS = ${SRCS:.c=.o}

BOBJS = ${BSRCS:.c=.o}

CC = gcc -c

FLAGS = -Wall -Werror -Wextra

GREEN = "\033[32m"
RED = "\033[31m"
YELLOW = "\033[33m"
NOCOLOR = "\033[0m"

%.o : %.c
	@${CC} ${FLAGS} $< -o $@

${NAME}: ${OBJS} libft.h
	@echo $(YELLOW)Norminette...$(NOCOLOR)
	@norminette $(SCRS)
	@echo $(GREEN)Compiling source files... $(NOCOLOR)
	@ar rcs ${NAME} ${OBJS}
	@echo $(GREEN)Library $(NOCOLOR)$(NAME) $(GREEN)ready$(NOCOLOR)

all: ${NAME}

clean:
	@${RM} ${OBJS} ${BOBJS}
	@echo Objects files $(RED)cleaned$(NOCOLOR)

fclean: clean
	@${RM} ${NAME}
	@echo Library file $(NAME) $(RED)cleaned$(NOCOLOR)

re: fclean all

bonus: ${OBJS} ${BOBJS} libft.h
	ar rcs ${NAME} ${OBJS} ${BOBJS}

.PHONY: clean fclean re all bonus