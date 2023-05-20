
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
