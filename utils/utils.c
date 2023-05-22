
#include "../philo.h"

long int	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	improve_usleep(long int time, t_base *base)
{
	long int	i;

	i = timestamp();
	while (base->died == 0)
	{
		if (timestamp() - i >= time)
			break ;
		usleep(50);
	}
}
