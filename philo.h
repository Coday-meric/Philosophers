/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 07:29:54 by amaisonn          #+#    #+#             */
/*   Updated: 2023/05/30 07:29:54 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_base
{
	pthread_mutex_t	print_mutex;
	long int		time_start;
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_max_eat;
	int				died;
}	t_base;

typedef struct s_philo
{
	pthread_mutex_t	fork_mutex;
	pthread_t		pid;
	long int		last_eat;
	int				nbr_eat;
	int				num_philo;
	int				fork;
	int				nbr_fork;
	t_base			*base;
	struct s_philo	*start;
	struct s_philo	*next;
}	t_philo;

//CORE
int		check_args(t_base *base, int argc, char **argv);
void	*thread_routine(void *data);
void	add_thread(t_base *base, t_philo *philo, t_philo *philo_start, int nbr);
void	fork_l_out(t_philo *philo);
void	fork_r_out(t_philo *philo);
void	fork_r(t_philo *philo);
void	fork_l(t_philo *philo);
t_philo	*new_thread(t_base *base, t_philo *philo_start, int nbr);

//MAIN
void	error(t_base *base, int code);
void	message(t_philo *philo, int code, long int time);

//UTILS

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		check_final(t_philo *philo, t_base *base);
int		check_die(t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t ec, size_t es);
void	improve_usleep(long int time, t_base *base);
long	timestamp(void);

#endif //PHILO_H
