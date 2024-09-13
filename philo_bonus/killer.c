/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:14:43 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/13 12:42:34 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_waiter(t_tab *tab)
{
	int	i;

	i = 0;
	while (i < tab->nb_philo)
	{
		waitpid(*tab->pids[i], NULL, 0);
		i++;
	}
}

int	alive_check(t_philo *p)
{
	int	res;

	sem_wait(p->alive_sem);
	res = p->alive;
	sem_post(p->alive_sem);
	return (res);
}

void	*meal_checker(void	*args)
{
	t_tab	*tab;
	int		i;

	i = 0;
	tab = (t_tab *) args;
	while (i < tab->nb_philo)
	{
		sem_wait(tab->sem_meals);
		i++;
	}
	sem_post(tab->stop);
	sem_wait(tab->sem_print);
	printf("\033[1m\033[33m %ld \033[1m\033[35m MAX MEALS REACHED\n", \
	ft_time() - tab->start_time);
	return (NULL);
}

void	sim_stopper(t_tab *tab)
{
	int	i;

	i = 0;
	while (i < tab->nb_philo)
	{
		kill(*tab->pids[i], SIGKILL);
		i++;
	}
}

void	*killer(void *args)
{
	t_tab	*tab;
	time_t	time;

	tab = (t_tab *) args;
	while (*tab->killed == 0)
	{
		time = ft_time();
		sem_wait(tab->this_philo->dead_check);
		if (time - tab->this_philo->last_eat > tab->tt_die)
		{
			sem_wait(tab->sem_print);
			printf("\033[1m\033[33m %ld \033[1m\033[31m %d DIED \n", \
			ft_time() - tab->start_time, tab->this_philo->id + 1);
			sem_post(tab->stop);
			*tab->killed = 1;
		}
		if (tab->this_philo->alive == 0)
			return (NULL);
		sem_post(tab->this_philo->dead_check);
	}
	return (NULL);
}
