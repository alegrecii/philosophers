/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:17:07 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/24 18:15:36 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *p)
{
	long	tt_think;

	tt_think = (p->tt_die - (ft_time() - p->last_eat) - p->tt_eat) / 2;
	if (tt_think < 0)
		tt_think = 0;
	if (tt_think > 600)
		tt_think = 200;
	pthread_mutex_lock(p->printer);
	printf(" \033[1m\033[33m%ld \033[1m\033[32m %d IS THINKING \n", \
	ft_time() - p->start_time, p->id + 1);
	pthread_mutex_unlock(p->printer);
	ft_msleep(tt_think);
}

void	p_sleep(t_philo *p)
{
	pthread_mutex_lock(p->printer);
	printf(" \033[1m\033[33m%ld \033[1m\033[32m %d IS SLEEPING\n", \
	ft_time() - p->start_time, p->id + 1);
	pthread_mutex_unlock(p->printer);
	ft_msleep(p->tt_sleep);
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(p->printer);
	printf(" \033[1m\033[33m%ld \033[1m\033[32m %d IS EATING\n", \
	ft_time() - p->start_time, p->id + 1);
	pthread_mutex_unlock(p->printer);
	pthread_mutex_lock(p->t_eat_lock);
	p->meals++;
	p->last_eat = ft_time();
	pthread_mutex_unlock(p->t_eat_lock);
	ft_msleep(p->tt_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	take_forks(t_philo *p)
{
	if ((p->id) % 2 == 0 && p->id + 1 != p->nb_philo)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
	}
	if (alive_check(p))
	{
		pthread_mutex_lock(p->printer);
		printf(" \033[1m\033[33m%ld \033[1m\033[32m %d HAS TAKEN A FORK \n", \
		ft_time() - p->start_time, p->id + 1);
		printf(" \033[1m\033[33m%ld \033[1m\033[32m %d HAS TAKEN A FORK \n", \
		ft_time() - p->start_time, p->id + 1);
		pthread_mutex_unlock(p->printer);
	}
	else
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
}

void	*life_manager(void *philo)
{
	t_philo	*p;

	p = (t_philo *) philo;
	pthread_mutex_lock(p->t_eat_lock);
	p->last_eat = ft_time();
	pthread_mutex_unlock(p->t_eat_lock);
	while (1)
	{
		if (alive_check(p))
			take_forks(p);
		if (alive_check(p))
			eat(p);
		if (alive_check(p))
			p_sleep(p);
		if (alive_check(p))
			p_think(p);
		if (!alive_check(p))
			return (NULL);
	}
	return (NULL);
}
