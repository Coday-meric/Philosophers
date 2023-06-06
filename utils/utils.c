/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:01:54 by amaisonn          #+#    #+#             */
/*   Updated: 2023/05/30 08:01:54 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (1)
	{
		pthread_mutex_lock(&base->die_mutex);
		if (base->died == 1)
		{
			pthread_mutex_unlock(&base->die_mutex);
			break ;
		}
		pthread_mutex_unlock(&base->die_mutex);
		if (timestamp() - i >= time)
			break ;
		usleep(250);
	}
}

int	check_if_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->base->die_mutex);
	if (philo->base->died == 1)
	{
		pthread_mutex_unlock(&philo->base->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->base->die_mutex);
	return (0);
}
