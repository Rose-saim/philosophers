MANDA_NAMES	= conditions.c error.c ft_free.c ft_init.c ft_lst.c \
			  main_actions.c philosophers.c  secondary_actions.c\
			  status.c utils.c

MANDA_OBJS	= $(MANDA_NAMES:.c=.o)

NAME		= philosophers

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f

all:		$(NAME)

$(NAME):	$(MANDA_OBJS)
				$(CC) $(CFLAGS) $(MANDA_OBJS) -pthread -o $(NAME)

clean:
			$(RM) $(MANDA_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re%    
