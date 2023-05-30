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

t_philo	*new_thread(t_base *base, t_philo *philo_start, int nbr)
{
	t_philo			*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	philo->num_philo = nbr;
	philo->base = base;
	philo->fork = 0;
	philo->last_eat = timestamp();
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
		pthread_mutex_lock(&philo->fork_mutex);
		if (!philo->next)
		{
			pthread_mutex_unlock(&philo->fork_mutex);
			break ;
		}
		philo = philo->next;
		pthread_mutex_unlock(&philo->fork_mutex);
	}
	philo->next = new_thread(base, philo_start, nbr);
}
