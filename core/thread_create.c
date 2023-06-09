/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 07:43:22 by amaisonn          #+#    #+#             */
/*   Updated: 2023/05/30 07:43:22 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_thread(t_philo *philo)
{
	while (philo)
	{
		pthread_mutex_lock(&philo->last_eat_mutex);
		philo->last_eat = timestamp();
		pthread_mutex_unlock(&philo->last_eat_mutex);
		pthread_mutex_lock(&philo->fork_mutex);
		philo->fork = 0;
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_create(&philo->pid, NULL, thread_routine, philo);
		philo = philo->next;
	}
}

t_philo	*new_thread(t_base *base, t_philo *philo_start, int nbr)
{
	t_philo			*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	pthread_mutex_init(&philo->fork_mutex, NULL);
	pthread_mutex_init(&philo->last_eat_mutex, NULL);
	pthread_mutex_init(&philo->nbr_eat_mutex, NULL);
	pthread_mutex_init(&philo->nbr_fork_mutex, NULL);
	philo->num_philo = nbr;
	philo->base = base;
	philo->next = NULL;
	if (philo_start != NULL)
		philo->start = philo_start;
	else
		philo->start = philo;
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
