/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 07:43:32 by amaisonn          #+#    #+#             */
/*   Updated: 2023/05/30 07:43:32 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	got_to_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->base->die_mutex);
	if (philo->base->died == 1)
	{
		pthread_mutex_unlock(&philo->base->die_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->base->die_mutex);

	message(philo, 3, timestamp());
	improve_usleep(philo->base->time_sleep, philo->base);
}

static void	got_to_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->base->die_mutex);
	if (philo->base->died == 1)
	{
		pthread_mutex_unlock(&philo->base->die_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->base->die_mutex);

	message(philo, 4, timestamp());
}

static void	go_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->nbr_eat_mutex);
	philo->nbr_eat = philo->nbr_eat + 1;
	pthread_mutex_unlock(&philo->nbr_eat_mutex);

	message(philo, 2, timestamp());

	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->last_eat_mutex);

	improve_usleep(philo->base->time_eat, philo->base);
}

void	*thread_routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	philo->pid = pthread_self();
	if (philo->num_philo % 2 == 0)
		usleep(5000);
	while (1)
	{
		pthread_mutex_lock(&philo->base->die_mutex);
		if (philo->base->died == 1)
		{
			pthread_mutex_unlock(&philo->base->die_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->base->die_mutex);

		fork_l(philo);
		fork_r(philo);

		pthread_mutex_lock(&philo->nbr_fork_mutex);
		if (philo->nbr_fork == 2)
		{
			pthread_mutex_unlock(&philo->nbr_fork_mutex);
			go_to_eat(philo);
			fork_l_out(philo);
			fork_r_out(philo);
			got_to_sleep(philo);
			got_to_think(philo);
		}
		else
			pthread_mutex_unlock(&philo->nbr_fork_mutex);
	}
	return (NULL);
}
