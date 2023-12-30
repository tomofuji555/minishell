# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2023/12/30 23:56:26 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror 
# RL_FLAGS	=	-lreadline -L $(brew --prefix readline)/lib -I $(brew --prefix readline)/include
RL_FLAGS	=	-lreadline
SRCS		=	alloc_utils.c \
				expand_env_in_str.c \
				ft_getenv.c \
				is_equal_str_untill_delim.c \
				ft_strcmp.c \
				is_valuable_token.c \
				main.c
OBJS		=	$(SRCS:.c=.o)
LIBFTPATH	=	libft/

all : $(NAME)

$(NAME): $(OBJS)
	make all -C $(LIBFTPATH)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(OBJS) $(LIBFTPATH)libft.a -o $(NAME)

clean :
	make clean -C $(LIBFTPATH)
	rm -f $(OBJS)

fclean : clean
	make fclean -C $(LIBFTPATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
