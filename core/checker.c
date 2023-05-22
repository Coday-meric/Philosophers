
#include "../philo.h"

int	check_args(t_base *base, int argc, char **argv)
{
	if (argc < 5)
		return (error(base, -1), 0);
	base->nbr_philo = ft_atoi(argv[1]);
	base->time_die = ft_atoi(argv[2]);
	base->time_eat = ft_atoi(argv[3]);
	base->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		base->nbr_max_eat = ft_atoi(argv[5]);
	return (1);
}

int	check_final(t_philo *philo, t_base *base)
{
	t_philo	*philo_loc;
	int i;

	philo_loc = philo;
	i = 0;
	while (philo_loc)
	{
		if (pthread_join(philo_loc->pid, NULL) == 0)
			return (0);
		if (philo_loc->nbr_eat >= base->nbr_max_eat)
			i++;
		philo_loc = philo_loc->next;
	}
	if (i == base->nbr_philo)
		return (0);
	return (1);
}

int	check_die(t_philo *philo)
{
	struct timeval	tv;
	long int		diff;

	gettimeofday(&tv, NULL);
	diff = tv.tv_usec - philo->last_eat;
	if (diff > (philo->base->time_die + 1000))
		return (message(philo, 5, tv.tv_usec), 0);
	return (1);
}
