/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:05:41 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/10 16:12:33 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	ft_time(void)
{
	struct timeval	tmp;
	time_t			time;

	gettimeofday(&tmp, NULL);
	time = 1000 * tmp.tv_sec + tmp.tv_usec / 1000;
	return (time);
}

void	ft_msleep(time_t ms)
{
	time_t	time;

	time = ft_time();
	usleep(ms * 920);
	while (time + ms > ft_time())
		usleep(ms);
}

void	ft_mega_free(t_tab *tab)
{
	int	i;

	sem_close(tab->sem_print);
	sem_close(tab->forks);
	sem_close(tab->t_grab);
	sem_close(tab->stop);
	sem_close(tab->sem_meals);
	i = 0;
	while (i < tab->nb_philo)
	{
		free(tab->pids[i]);
		i++;
	}
	free(tab->pids);
	free(tab->killed);
	free(tab->free_forks);
	i = 0;
	while (i < tab->nb_philo)
	{
		free(tab->philos[i]);
		i++;
	}
	free(tab->philos);
}
