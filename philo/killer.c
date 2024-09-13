/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:00:02 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/24 18:17:37 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alive_check(t_philo *p)
{
	int	res;

	pthread_mutex_lock(p->alive_lock);
	res = p->alive;
	pthread_mutex_unlock(p->alive_lock);
	return (res);
}

int	meal_counter(t_tab *tab)
{
	int	i;

	i = 0;
	if (tab->max_eat == -1)
		return (0);
	while (i < tab->nb_philo)
	{
		if (tab->philos[i].meals < tab->max_eat)
			return (0);
		i++;
	}
	return (1);
}

void	sim_stopper(t_philo *philos, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_lock(philos[i].alive_lock);
		philos[i].alive = 0;
		pthread_mutex_unlock(philos[i].alive_lock);
		i++;
	}
}

void	stopper(t_tab *tab, int i)
{
	if (i == -1)
	{
		sim_stopper(tab->philos, tab->nb_philo);
	}
	else
	{
		sim_stopper(tab->philos, tab->nb_philo);
		pthread_mutex_lock(tab->printer);
		printf("\033[1m\033[33m %ld \033[1m\033[31m %d DIED \n", \
		ft_time() - tab->start_time, i + 1);
		pthread_mutex_unlock(tab->printer);
		tab->killed = 1;
	}
	pthread_mutex_unlock(tab->t_eat_lock);
}

void	*killer(void *args)
{
	t_tab	*tab;
	long	time;
	int		i;

	tab = (t_tab *) args;
	while (tab->killed == 0)
	{
		time = ft_time();
		i = 0;
		while (i < tab->nb_philo)
		{
			pthread_mutex_lock(tab->t_eat_lock);
			if (time - tab->philos[i].last_eat > tab->tt_die)
				stopper(tab, i);
			if (meal_counter(tab))
				stopper(tab, -1);
			if (tab->philos[i].alive == 0)
				return (NULL);
			pthread_mutex_unlock(tab->t_eat_lock);
			i++;
		}
	}
	return (NULL);
}
