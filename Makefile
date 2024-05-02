# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/05/02 22:22:48 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

CC		:=	cc -fsanitize=address
CFLAGS	:=	-Wall -Wextra -Werror 

ifeq ($(shell uname -s), Linux)
    
else
	RL_LIB_FLAG	:=	-L $(shell brew --prefix readline)/lib
	RL_H_FLAG	:=	-I $(shell brew --prefix readline)/include
	RL_FLAGS	:=	-lreadline $(RL_LIB_FLAG) $(RL_H_FLAG)
endif

LIBFT_PATH	:=	libft/
LIBFT_A		:=	$(LIBFT_PATH)libft.a

ROOT_SRCS		:=	main.c \
					main_utils.c
TOKEN_SRCS		:=	env_token.c \
					free_lst_all.c \
					input_token.c \
					lst_add_back.c \
					lstlast.c \
					output_token.c \
					pipe_token.c \
					quort_token.c \
					space_token.c \
					text_token.c \
					tokenize.c \
					tokenize_wrap.c \
					validate_syntax.c
PARSE_SRCS		:=	left_node.c \
					move_to_redir_tokens.c \
					parse.c \
					parse_wrap.c \
					prev_node.c \
					right_node.c 
EXPANSION_SRCS	:=	expand_env_tkn.c \
					expansion.c \
					expnad_env_in_dquote.c \
					make_cmd_args.c \
					make_redir_list.c \
					make_redir_list_utils.c \
					substr_from_tkn.c \
					utils_from_tokenize_tozeki.c
EXEC_SRCS		:=	do_single_builtin.c \
					exec_cmds.c \
					exec_cmds_utils.c \
					exec_external_cmd.c \
					execute.c \
					execute_utils.c \
					try_change_stream_redirect.c \
					try_heredoc.c \
					try_heredoc_utils.c
BUILTIN_SRCS	:=	builtin_cd.c \
					builtin_cd_utils.c \
					builtin_cd_utils2.c \
					builtin_echo.c \
					builtin_env.c \
					builtin_exit.c \
					builtin_exit_utils.c \
					builtin_export.c \
					builtin_export_utils.c \
					builtin_pwd.c \
					builtin_unset.c
UTILS_SRCS		:=	utils.c \
					utils_bool.c \
					utils_bool2.c \
					utils_env.c \
					utils_env2.c \
					utils_error.c \
					utils_free.c \
					utils_free2.c \
					utils_free3.c \
					utils_libftwrap.c \
					utils_libftwrap2.c \
					utils_print.c \
					utils_print2.c \
					utils_print3.c \
					utils_syswrap.c \
					utils_syswrap2.c \
					utils_token.c

SRCS	:=	$(ROOT_SRCS)
SRCS	+=	$(addprefix token/, $(TOKEN_SRCS))
SRCS	+=	$(addprefix parse/, $(PARSE_SRCS))
SRCS	+=	$(addprefix expansion/, $(EXPANSION_SRCS))
SRCS	+=	$(addprefix execute/, $(EXEC_SRCS))
SRCS	+=	$(addprefix builtin/, $(BUILTIN_SRCS))
SRCS	+=	$(addprefix utils/, $(UTILS_SRCS))
OBJS	:=	$(patsubst %.c, %.o, $(SRCS))


all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(LIBFT_A) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(RL_H_FLAG) -c $< -o $@

$(LIBFT_A): $(LIBFT_PATH)*.c
	make all -C $(LIBFT_PATH)
	
clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re