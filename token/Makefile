# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tofujiwa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2023/11/30 16:50:13 by tofujiwa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tokenize
CC = cc
CFLAGS = -Wall -Wextra -Werror
RL_FLAGS = -lreadline -lhistory
SRCS = tokenize.c lstlast.c lst_add_back.c ft_strdup.c ft_strlen.c ft_substr.c free_lst_all.c text_token.c space_token.c quort_token.c env_token.c pipe_token.c input_token.c output_token.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(RL_FLAGS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
