# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/04/10 21:22:08 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
#CFLAGS		=	-Wall -Wextra -Werror 
RL_LIB_FLAG	=	-L $(shell brew --prefix readline)/lib
RL_H_FLAG	=	-I $(shell brew --prefix readline)/include
RL_FLAGS	=	-lreadline  $(RL_LIB_FLAG) $(RL_H_FLAG)
OBJS		=	_utils_bool.o \
				_utils_env.o \
				_utils_free.o \
				_utils_libftwrap.o \
				_utils_print.o \
				_utils_syswrap.o \
				_utils_tkn.o \
				_utils.o \
				is_longlong_over.o \
				init.o \
				tokenize.o \
				parse.o \
				expansion.o\
				execute.o \
				run_heredoc.o \
				builtin_cd.o \
				builtin_exit.o \
				builtin_export.o \
				builtin_env.o \
				builtin_unset.o \
				main.o
LIBFT_PATH	=	libft/

all : $(NAME)

$(NAME): $(OBJS)
	make all -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(OBJS) $(LIBFT_PATH)libft.a -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(RL_H_FLAG) -c $<

clean :
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean : clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
