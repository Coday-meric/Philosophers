
#include "../philo.h"

//sa fourchette
static void	fork_l(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (philo->fork == 0)
	{
		message(philo, 1);
		philo->fork = 1;
		philo->nbr_fork = philo->nbr_fork + 1;
	}
	pthread_mutex_unlock(&philo->fork_mutex);
}

static void	fork_r(t_philo *philo)
{
	t_philo	*philo_next;

	if (philo->next == NULL)
		philo_next = philo->start;
	else
		philo_next = philo->next;

	pthread_mutex_lock(&philo_next->fork_mutex);

	if (philo_next->fork == 0)
	{
		message(philo, 1);
		philo_next->fork = 1;
		philo->nbr_fork = philo->nbr_fork + 1;
	}

	pthread_mutex_unlock(&philo_next->fork_mutex);
}

static void	fork_r_out(t_philo *philo)
{
	t_philo	*philo_next;

	if (philo->next == NULL)
		philo_next = philo->start;
	else
		philo_next = philo->next;
	pthread_mutex_lock(&philo_next->fork_mutex);
	if (philo_next->fork == 1)
	{
		message(philo, 6);
		philo_next->fork = 0;
		philo->nbr_fork = philo->nbr_fork - 1;
	}
	pthread_mutex_unlock(&philo_next->fork_mutex);
}

static void	fork_l_out(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (philo->fork == 1)
	{
		message(philo, 6);
		philo->fork = 0;
		philo->nbr_fork = philo->nbr_fork - 1;
	}
	pthread_mutex_unlock(&philo->fork_mutex);
}

static void	got_to_sleep(t_philo *philo)
{
	message(philo, 3);
	philo->state = 2;
	usleep(philo->base->time_sleep);
}

static void	got_to_think(t_philo *philo)
{
	message(philo, 4);
	philo->state = 3;
}

void	*thread_routine(void *data)
{
	struct timeval	tv;
	t_philo			*philo;
	t_base			*base;

	philo = (t_philo *)data;
	base = philo->base;
	philo->pid = pthread_self();
	gettimeofday(&tv, NULL);
	philo->last_eat = tv.tv_usec;
	pthread_mutex_lock(&base->print_mutex);
	printf("Nomre Total philo : %d, Thread Numero : %lu, Philo Numero : %d, Philo last eat : %lu\n", base->nbr_philo, philo->pid, philo->num_philo, philo->last_eat);
	pthread_mutex_unlock(&base->print_mutex);
	usleep(1000);
	while (check_die(philo))
	{
		fork_l(philo);
		fork_r(philo);

		if (philo->nbr_fork == 2)
		{
			message(philo, 2);
			philo->state = 1;
			usleep(philo->base->time_eat);
			gettimeofday(&tv, NULL);
			philo->last_eat = tv.tv_usec;
			philo->nbr_eat = philo->nbr_eat + 1;
			fork_l_out(philo);
			fork_r_out(philo);
			got_to_sleep(philo);
			got_to_think(philo);
		}
	}
	return (NULL);
}

t_philo	*new_thread(t_base *base, t_philo *philo_start, int nbr)
{
	struct timeval	tv;
	t_philo			*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	gettimeofday(&tv, NULL);
	philo->num_philo = nbr;
	philo->base = base;
	philo->fork = 0;
	philo->state = 0;
	philo->next = NULL;
	if (philo_start != NULL)
		philo->start = philo_start;
	else
		philo->start = philo;
	pthread_mutex_init(&philo->fork_mutex, NULL);
	pthread_create(&philo->pid, NULL, thread_routine, philo);
	return (philo);
}

void	add_thread(t_base *base, t_philo *philo, t_philo *philo_start, int nbr)
{
	while (philo)
	{
		if (!philo->next)
			break ;
		philo = philo->next;
	}
	philo->next = new_thread(base, philo_start, nbr);
}
