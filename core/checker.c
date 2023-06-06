/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 07:43:46 by amaisonn          #+#    #+#             */
/*   Updated: 2023/05/30 07:43:46 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_args2(t_base *base, char **argv)
{
	long long	tmp;

	tmp = ft_atoi(argv[1]);
	if (tmp == 2147483649)
		return (error(base, -2), 0);
	base->nbr_philo = tmp;
	tmp = ft_atoi(argv[2]);
	if (tmp == 2147483649)
		return (error(base, -2), 0);
	base->time_die = tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp == 2147483649)
		return (error(base, -2), 0);
	base->time_eat = tmp;
	return (1);
}

int	check_args(t_base *base, int argc, char **argv)
{
	long long	tmp;

	if (argc < 5)
		return (error(base, -1), 0);
	if (check_args2(base, argv) == 0)
		return (0);
	tmp = ft_atoi(argv[4]);
	if (tmp == 2147483649)
		return (error(base, -2), 0);
	base->time_sleep = tmp;
	if (argc == 6)
	{
		tmp = ft_atoi(argv[5]);
		if (tmp == 2147483649)
			return (error(base, -2), 0);
		base->nbr_max_eat = tmp;
	}
	else
		base->nbr_max_eat = -1;
	return (1);
}

int	check_die(t_philo *philo)
{
	long int		diff;
	long int		time;

	time = timestamp();
	pthread_mutex_lock(&philo->last_eat_mutex);
	diff = time - philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (diff > (philo->base->time_die))
		return (message(philo, 5, time), 0);
	return (1);
}

static int	check_nbr_philo_eat(t_base *base, int i)
{
	if (base->nbr_max_eat != -1)
	{
		if (i == base->nbr_philo)
		{
			pthread_mutex_lock(&base->die_mutex);
			base->died = 1;
			pthread_mutex_unlock(&base->die_mutex);
			return (0);
		}
	}
	return (1);
}

int	check_final(t_philo *philo, t_base *base)
{
	t_philo	*philo_loc;
	int		i;

	philo_loc = philo;
	i = 0;
	while (philo_loc)
	{
		if (check_die(philo) == 0)
		{
			pthread_mutex_lock(&base->die_mutex);
			base->died = 1;
			pthread_mutex_unlock(&base->die_mutex);
			return (0);
		}
		pthread_mutex_lock(&philo_loc->nbr_eat_mutex);
		if (base->nbr_max_eat != -1)
			if (philo_loc->nbr_eat >= base->nbr_max_eat)
				i++;
		pthread_mutex_unlock(&philo_loc->nbr_eat_mutex);
		philo_loc = philo_loc->next;
	}
	if (check_nbr_philo_eat(base, i) == 0)
		return (0);
	return (1);
}
