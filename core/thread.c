
#include "../philo.h"

void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->pid = pthread_self();
	printf("Thread Numero : %lu, Philo Numero : %d, Philo last eat : %lu\n", philo->pid, philo->nbr_philo, philo->last_eat);
	return (NULL);
}

t_philo	*new_thread(int nbr)
{
	struct timeval	tv;
	t_philo			*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	gettimeofday(&tv, NULL);
	philo->last_eat = tv.tv_usec;
	philo->nbr_philo = nbr;
	philo->next = NULL;
	pthread_create(&philo->pid, NULL, thread_routine, philo);
	return (philo);
}

void	add_thread(t_philo *philo, int nbr)
{
	while (philo)
	{
		if (!philo->next)
			break ;
		philo = (t_philo *) philo->next;
	}
	philo->next = (struct t_philo *)new_thread(nbr);
}
