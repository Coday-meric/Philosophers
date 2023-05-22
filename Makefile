INCMYUTILS=./utils/
INCCORE=./core/

NAME = philo

SRC = main.c $(INCCORE)checker.c $(INCCORE)thread.c $(INCMYUTILS)ft_atoi.c $(INCMYUTILS)ft_calloc.c $(INCMYUTILS)ft_bzero.c $(INCMYUTILS)ft_isdigit.c $(INCMYUTILS)ft_putchar_fd.c $(INCMYUTILS)ft_putstr_fd.c $(INCMYUTILS)ft_putnbr_fd.c

FLAG = -Wall -Werror -Wextra -pthread

BUG = -fsanitize=address

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):	$(OBJ)
		gcc $(FLAG) -o $(NAME) $(OBJ)

debug:
	gcc $(BUG) $(FLAG) -o $(NAME) $(OBJ)

clean:
	rm -rf *.o
	rm -rf $(INCMYUTILS)*.o
	rm -rf $(INCCORE)*.o

fclean: clean
	rm -rf $(NAME)

re: clean all