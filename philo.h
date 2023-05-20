
#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_base
{
	int	nbr_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nbr_max_eat;
}	t_base;

typedef struct s_philo
{
	pthread_t		pid;
	long int		last_eat;
	int				nbr_eat;
	int				nbr_philo;
	struct t_philo	*next;
}	t_philo;

//CORE
int		check_args(t_base *base, int argc, char **argv);
void	*thread_routine(void *data);
void	add_thread(t_philo *philo, int nbr);
t_philo	*new_thread(int nbr);

//MAIN
void	error(t_base *base, int code);

//UTILS
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t ec, size_t es);

#endif //PHILO_H
