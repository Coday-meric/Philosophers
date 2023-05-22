
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
	else
		base->nbr_max_eat = -1;
	return (1);
}

int	check_die(t_philo *philo)
{
	long int		diff;
	long int		time;

	time = timestamp();
	diff = time - philo->last_eat;
	if (diff > (philo->base->time_die))
		return (message(philo, 5, time), 0);
	return (1);
}

int	check_final(t_philo *philo, t_base *base)
{
	t_philo	*philo_loc;
	int		i;

	philo_loc = philo;
	i = 0;
	while (philo_loc)
	{
		if (check_die(philo) == 0)
		{
			base->died = 1;
			return (0);
		}
		if (base->nbr_max_eat != -1)
			if (philo_loc->nbr_eat >= base->nbr_max_eat)
				i++;
		philo_loc = philo_loc->next;
	}
	if (base->nbr_max_eat != -1)
	{
		if (i == base->nbr_philo)
		{
			base->died = 1;
			return (0);
		}
	}
	return (1);
}
