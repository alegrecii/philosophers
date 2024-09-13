NAME = philo

SRCS = philo.c \
		ft_input_error.c \
		lib_utils.c \
		utils.c \
		simulation.c \
		killer.c \
		mega_free.c \


OBJS = $(SRCS:.c=.o)


CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME) : $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
				$(RM) $(OBJS)

fclean : clean
				$(RM) $(NAME)

re : fclean all

