/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:55:45 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/13 12:51:01 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	p_think(t_philo *p)
{
	time_t	tt_think;

	tt_think = (p->tt_die - (ft_time() - p->last_eat) - p->tt_eat) / 2;
	if (tt_think < 0)
		tt_think = 0;
	if (tt_think > 600)
		tt_think = 200;
	sem_wait(p->sem_print);
	printf(" \033[1m\033[33m%ld \033[1m\033[32m %d IS THINKING \n", \
	ft_time() - p->start_time, p->id + 1);
	sem_post(p->sem_print);
	ft_msleep(tt_think);
}

void	p_sleep(t_philo *p)
{
	sem_wait(p->sem_print);
	printf(" \033[1m\033[33m%ld \033[1m\033[32m %d IS SLEEPING\n", \
	ft_time() - p->start_time, p->id + 1);
	sem_post(p->sem_print);
	ft_msleep(p->tt_sleep);
}

void	eat(t_philo *p, t_tab *t)
{
	sem_wait(p->sem_print);
	printf(" \033[1m\033[33m%ld \033[1m\033[32m %d IS EATING\n", \
	ft_time() - p->start_time, p->id + 1);
	sem_post(p->sem_print);
	sem_wait(p->dead_check);
	p->meals++;
	p->last_eat = ft_time();
	sem_post(p->dead_check);
	ft_msleep(p->tt_eat);
	if (p->meals == p->max_eat)
		sem_post(p->sem_meals);
	sem_post(t->forks);
	sem_post(t->forks);
	*t->free_forks += 2;
}

void	take_forks(t_philo *p, t_tab *t)
{
	int	taken;

	taken = 0;
	while (taken == 0)
	{
		sem_wait(p->grab);
		if (*t->free_forks >= 2)
		{
			*t->free_forks -= 2;
			sem_wait(t->forks);
			sem_wait(t->forks);
			sem_wait(p->sem_print);
			printf(" \033[1m\033[33m%ld \033[1m\033[32m %d HAS TAKEN A FORK \n", \
			ft_time() - p->start_time, p->id + 1);
			printf(" \033[1m\033[33m%ld \033[1m\033[32m %d HAS TAKEN A FORK \n", \
			ft_time() - p->start_time, p->id + 1);
			sem_post(p->sem_print);
			taken = 1;
		}
		sem_post(p->grab);
	}
}

void	ft_life(t_tab *tab)
{
	t_philo	*p;

	p = tab->this_philo;
	personal_sem_init(p);
	p->last_eat = ft_time();
	pthread_create(&tab->killer, NULL, killer, tab);
	while (1)
	{
		if (alive_check(p))
			take_forks(p, tab);
		if (alive_check(p))
			eat(p, tab);
		if (alive_check(p))
			p_sleep(p);
		if (alive_check(p))
			p_think(p);
		if (!alive_check(p))
			return ;
	}
}
