# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/01/20 18:44:30 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror 
# RL_FLAGS	=	-lreadline -L $(brew --prefix readline)/lib -I $(brew --prefix readline)/include
RL_FLAGS	=	-lreadline
SRCS		=	_alloc_utils.c \
				_bool_utils.c \
				_check_print_utils.c \
				_env_utils.c \
				_free_utils.c \
				_fujiwa_utils.c \
				_redir_utils.c \
				_tkn_utils.c \
				_utils_1.c \
				tokenize.c \
				tokenize_utils1.c \
				tokenize_utils2.c \
				tokenize_utils3.c \
				parse.c \
				parse_utils1.c \
				parse_utils2.c \
				expansion.c \
				expand_env.c \
				expand_env_in_dquote.c \
				make_redir_list.c \
				make_cmd_args.c \
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
