# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/04/12 23:27:16 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
CC			:=	cc
#CFLAGS		:=	-Wall -Wextra -Werror 
RL_LIB_FLAG	:=	-L $(shell brew --prefix readline)/lib
RL_H_FLAG	:=	-I $(shell brew --prefix readline)/include
RL_FLAGS	:=	-lreadline  $(RL_LIB_FLAG) $(RL_H_FLAG)
LIBFT_PATH	:=	libft/
TOKENIZE_PATH :=	token/
PARSE_PATHS	:=	parse/
PATHS		:=	$(LIBFT_PATH) $(TOKENIZE_PATH) $(PARSE_PATHS) ./
ALL_SRCS	:=	$(foreach path, $(PATHS), $(path)*.c)
SRCS		:=	test_main.o \
				test_print.o 
OBJS		:=	$(LIBFT_PATH)*.a $(TOKENIZE_PATH)*.o $(PARSE_PATHS)*.o ./*.o

all : $(NAME)

$(NAME): $(SRCS)
	make all -C $(LIBFT_PATH)
	make all -C $(TOKENIZE_PATH)
	make all -C $(PARSE_PATHS)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(RL_H_FLAG) -c $<	

clean :
	make clean -C libft/
	make clean -C parse/
	make clean -C token/
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re