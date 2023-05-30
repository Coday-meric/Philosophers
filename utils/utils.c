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
	while (base->died == 0)
	{
		if (timestamp() - i >= time)
			break ;
		usleep(250);
	}
}
