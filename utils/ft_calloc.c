/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:42:21 by amaisonn          #+#    #+#             */
/*   Updated: 2023/02/08 13:07:47 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_calloc(size_t ec, size_t es)
{
	void	*ptr;

	if (ec == 0 || es == 0)
		return (malloc(0));
	if ((ec * es) / es != ec)
		return (0);
	ptr = (void *)malloc(ec * es);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, ec * es);
	return (ptr);
}
