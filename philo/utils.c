/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:41 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/20 15:02:41 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time(void)
{
	struct timeval	tmp;
	long int		time;

	gettimeofday(&tmp, NULL);
	time = 1000 * (size_t)tmp.tv_sec + (size_t)tmp.tv_usec / 1000;
	return (time);
}

void	ft_msleep(long ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (time + ms > ft_time())
		usleep(ms);
}
