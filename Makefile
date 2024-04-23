# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/04/23 23:47:33 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
CC			:=	cc
# CFLAGS		:=	-Wall -Wextra -Werror 
RL_LIB_FLAG	:=	-L $(shell brew --prefix readline)/lib
RL_H_FLAG	:=	-I $(shell brew --prefix readline)/include
RL_FLAGS	:=	-lreadline $(RL_LIB_FLAG) $(RL_H_FLAG)
LIBFT_PATH	:=	libft/
LIBFT_A		:=	$(LIBFT_PATH)libft.a
SRC_PATHS	:=	$(LIBFT_PATH) \
				utils/ \
				token_tozeki/ \
				parse/ \
				expansion/ \
				execute/ \
				builtin/ \
				./
SRCS		:=	$(foreach path, $(SRC_PATHS), $(wildcard $(path)*.c))
OUT_PATTERN	:=	$(LIBFT_PATH)% \
				./main_test.c \
				parse/syntax_check.c
OBJS		:=	$(patsubst %.c, %.o, $(filter-out $(OUT_PATTERN), $(SRCS)))


all:	$(NAME)

$(NAME): $(OBJS)
	make all -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(LIBFT_A) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(RL_H_FLAG) -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re