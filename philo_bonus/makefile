NAME = philo_bonus

SRCS = philo_bonus.c \
		ft_input_error.c \
		lib_utils.c \
		life_manager.c \
		killer.c \
		sem_init.c \
		init.c \
		utils.c \




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

