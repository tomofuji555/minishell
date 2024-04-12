# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/04/12 18:39:43 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RL_LIB_FLAG	=	-L $(shell brew --prefix readline)/lib
RL_H_FLAG	=	-I $(shell brew --prefix readline)/include
RL_FLAGS	=	-lreadline  $(RL_LIB_FLAG) $(RL_H_FLAG)
SRCS = parse_wrap.c parse.c right_node.c left_node.c prev_node.c syntax_check.c
OBJS = $(SRCS:.c=.o)
OBJS_PATH =../objs

all : $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
