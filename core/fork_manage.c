/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 07:43:39 by amaisonn          #+#    #+#             */
/*   Updated: 2023/05/30 07:43:39 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	fork_l(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (philo->fork == 0 && philo->base->died == 0)
	{
		message(philo, 1, timestamp());
		philo->fork = 1;
		philo->nbr_fork = philo->nbr_fork + 1;
	}
	pthread_mutex_unlock(&philo->fork_mutex);
}

void	fork_r(t_philo *philo)
{
	t_philo	*philo_next;

	if (philo->next == NULL)
		philo_next = philo->start;
	else
		philo_next = philo->next;

	pthread_mutex_lock(&philo_next->fork_mutex);

	if (philo_next->fork == 0 && philo->base->died == 0)
	{
		message(philo, 1, timestamp());
		philo_next->fork = 1;
		philo->nbr_fork = philo->nbr_fork + 1;
	}

	pthread_mutex_unlock(&philo_next->fork_mutex);
}

void	fork_r_out(t_philo *philo)
{
	t_philo	*philo_next;

	if (philo->next == NULL)
		philo_next = philo->start;
	else
		philo_next = philo->next;
	pthread_mutex_lock(&philo_next->fork_mutex);
	if (philo_next->fork == 1)
	{
		philo_next->fork = 0;
		philo->nbr_fork = philo->nbr_fork - 1;
	}
	pthread_mutex_unlock(&philo_next->fork_mutex);
}

void	fork_l_out(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (philo->fork == 1)
	{
		philo->fork = 0;
		philo->nbr_fork = philo->nbr_fork - 1;
	}
	pthread_mutex_unlock(&philo->fork_mutex);
}
