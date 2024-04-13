# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/04/13 23:18:22 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
CC			:=	cc
# CFLAGS		:=	-Wall -Wextra -Werror 
RL_LIB_FLAG	:=	-L $(shell brew --prefix readline)/lib
RL_H_FLAG	:=	-I $(shell brew --prefix readline)/include
RL_FLAGS	:=	-lreadline  $(RL_LIB_FLAG) $(RL_H_FLAG)
LIBFT_PATH	:=	libft/
LIBFT_A		:=	$(LIBFT_PATH)libft.a
SRC_PATHS	:=	$(LIBFT_PATH) token/ parse/ ./
SRCS		:=	$(foreach path, $(SRC_PATHS), $(wildcard $(path)*.c))
OUT_PATTERN	:=	$(LIBFT_PATH)%
OBJS		:=	$(patsubst %.c, %.o, $(filter-out $(OUT_PATTERN), $(SRCS)))


all:	$(NAME)

$(NAME): $(OBJS)
	make all -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(OBJS) $(LIBFT_A) -o $@

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