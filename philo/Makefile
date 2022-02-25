MANDA_NAMES	= philosophers.c ft_init.c error.c events.c \
			  ft_lst.c utils.c status.c

MANDA_OBJS	= $(MANDA_NAMES:.c=.o)

NAME		= philosophers

CC			= clang
CFLAGS		= -Wall -Wextra -Werror

RM = rm -f

all:		$(NAME)

$(NAME):	$(MANDA_OBJS)
				$(CC) -pthread $(CFLAGS) $(MANDA_OBJS) -pthread -o $(NAME)

clean:
			$(RM) $(MANDA_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re%    
