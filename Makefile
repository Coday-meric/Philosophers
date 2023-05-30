INCMYUTILS=./utils/
INCCORE=./core/

NAME = philo

SRC = main.c $(INCCORE)checker.c $(INCCORE)thread.c $(INCCORE)thread_create.c $(INCCORE)fork_manage.c $(INCMYUTILS)utils.c $(INCMYUTILS)ft_atoi.c $(INCMYUTILS)ft_calloc.c $(INCMYUTILS)ft_bzero.c $(INCMYUTILS)ft_isdigit.c $(INCMYUTILS)ft_putchar_fd.c $(INCMYUTILS)ft_putstr_fd.c $(INCMYUTILS)ft_putnbr_fd.c

FLAG = -g -Wall -Werror -Wextra -pthread

BUG = -fsanitize=thread

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):	$(OBJ)
		gcc -g $(FLAG) -o $(NAME) $(OBJ)

debug:
	gcc $(BUG) $(FLAG) -o $(NAME) $(OBJ)

clean:
	rm -rf *.o
	rm -rf $(INCMYUTILS)*.o
	rm -rf $(INCCORE)*.o

fclean: clean
	rm -rf $(NAME)

re: clean all