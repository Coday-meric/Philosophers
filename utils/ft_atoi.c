/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:58:09 by amaisonn          #+#    #+#             */
/*   Updated: 2023/02/07 14:02:48 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	res = 0;
	signe = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i] == 45)
			signe = -1;
		i++;
	}
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (2147483649);
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * signe);
}
