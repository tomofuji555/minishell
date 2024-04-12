# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/04/12 18:39:50 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RL_LIB_FLAG	=	-L $(shell brew --prefix readline)/lib
RL_H_FLAG	=	-I $(shell brew --prefix readline)/include
RL_FLAGS	=	-lreadline  $(RL_LIB_FLAG) $(RL_H_FLAG)
SRCS = tokenize_wrap.c tokenize.c lstlast.c lst_add_back.c free_lst_all.c text_token.c space_token.c quort_token.c env_token.c pipe_token.c input_token.c output_token.c 
OBJS = $(SRCS:.c=.o)
OBJS_PATH =../objs

all : $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
