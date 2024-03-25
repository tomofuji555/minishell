# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/03/26 04:09:52 by tozeki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
#CFLAGS		=	-Wall -Wextra -Werror 
RL_FLAGS	=	-lreadline -L $(brew --prefix readline)/lib -I $(brew --prefix readline)/include
RL_FLAGS	=	-lreadline
OBJS		=	_utils_bool.o \
				_utils_env.o \
				_utils_free.o \
				_utils_libftwrap.o \
				_utils_print.o \
				_utils_syswrap.o \
				_utils_tkn.o \
				_utils.o \
				init.o \
				tokenize.o \
				parse.o \
				expansion.o\
				execute.o \
				run_heredoc.o \
				main.o
LIBFTPATH	=	libft/

all : $(NAME)

$(NAME): $(OBJS)
	make all -C $(LIBFTPATH)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(OBJS) $(LIBFTPATH)libft.a -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean :
	make clean -C $(LIBFTPATH)
	rm -f $(OBJS)

fclean : clean
	make fclean -C $(LIBFTPATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
