CC	=	cc
# CFLAGS	=	-Wall -Wextra -Werror -g
NAME	=	utils.a
SRCS	=	utils_1.c \
			alloc_utils.c \
			bool_utils.c \
			env_utils.c \
			make_redir_list_utils.c \
			tkn_utils.c \
			fujiwa_utils.c
OBJS	=	$(SRCS:.c=.o)
AR	=	ar rcs
RM	=	rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re

# debug: main.o $(OBJS)
# 	$(CC) $^ -o main.exe
