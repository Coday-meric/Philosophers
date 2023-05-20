/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymeric <aymeric@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 07:31:21 by aymeric           #+#    #+#             */
/*   Updated: 2023/05/20 07:31:21 by aymeric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	error(t_base *base, int code)
{
	if (code == -1)
		printf("Nombre d'argument incorrect !\n");
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_base		*base;
	int			i;

	i = 1;
	base = ft_calloc(1, sizeof(t_base));
	if (check_args(base, argc, argv) == 0)
		return (0);
	philo = new_thread(1);
	while (i < base->nbr_philo)
	{
		add_thread(philo, i + 1);
		i++;
	}
	while (1);
	return (1);
}


