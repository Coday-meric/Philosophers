/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 07:42:59 by amaisonn          #+#    #+#             */
/*   Updated: 2023/05/30 11:14:27 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(t_base *base, int code)
{
	if (code == -1)
		printf("Nombre d'argument incorrect !\n");
}

void	message(t_philo *philo, int code, long int time)
{
	pthread_mutex_lock(&philo->base->print_mutex);
	if (code == 1)
		printf("%lu %d has taken a fork\n"\
		, (time - philo->base->time_start), philo->num_philo);
	else if (code == 2)
		printf("\033[32;1m%lu %d is eating\n\033[0m"\
		, (time - philo->base->time_start), philo->num_philo);
	else if (code == 3)
		printf("\033[34;1m%lu %d is sleeping\n\033[0m"\
		, (time - philo->base->time_start), philo->num_philo);
	else if (code == 4)
		printf("\033[33;1m%lu %d is thinking\n\033[0m"\
		, (time - philo->base->time_start), philo->num_philo);
	else if (code == 5)
		printf("\033[31;1m%lu %d died\n\033[0m"\
		, (time - philo->base->time_start), philo->num_philo);
	pthread_mutex_unlock(&philo->base->print_mutex);
}

void	clean(t_base *base, t_philo *philo_start)
{
	t_philo	*philo_tmp;
	t_philo	*philo;

	philo = philo_start;
	while (philo)
	{
		pthread_join(philo->pid, NULL);
		philo = philo->next;
	}
	philo = philo_start;
	while (philo)
	{
		philo_tmp = philo->next;
		free(philo);
		philo = philo_tmp;
	}
	free(base);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_philo		*philo_start;
	t_base		*base;
	int			i;

	i = 1;
	base = ft_calloc(1, sizeof(t_base));
	if (check_args(base, argc, argv) == 0)
		return (0);
	pthread_mutex_init(&base->print_mutex, NULL);
	pthread_mutex_init(&base->die_mutex, NULL);
	base->died = 0;
	base->time_start = timestamp();
	philo = new_thread(base, NULL, 1);
	philo_start = philo;
	while (i < base->nbr_philo)
	{
		add_thread(base, philo, philo_start, i + 1);
		i++;
	}
	create_thread(philo_start);
	while (check_final(philo_start, base) == 1 && check_die(philo) == 1)
		usleep(1000);
	clean(base, philo_start);
	return (1);
}
