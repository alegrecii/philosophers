/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:38:03 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/13 12:49:27 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pid_init(pid_t **p, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		p[i] = malloc(sizeof(pid_t));
		i++;
	}
}

void	ft_variables_init(t_tab *tab, char **argv)
{
	int	*ff;

	tab->nb_philo = ft_atoi(argv[1]);
	tab->tt_die = ft_atoi(argv[2]);
	tab->tt_eat = ft_atoi(argv[3]);
	tab->tt_sleep = ft_atoi(argv[4]);
	tab->start_time = ft_time();
	tab->killed = malloc(sizeof(int));
	*tab->killed = 0;
	ff = malloc(sizeof(int));
	*ff = tab->nb_philo;
	tab->free_forks = ff;
}

void	ft_sem_init(t_tab *tab)
{
	sem_unlink("s_forks");
	sem_unlink("to_grab");
	sem_unlink("sem_stop");
	sem_unlink("sem_print");
	sem_unlink("sem_meals");
	tab->sem_print = sem_open("sem_print", O_CREAT, S_IRUSR | S_IWUSR, 1);
	tab->forks = sem_open("s_forks", O_CREAT, S_IRUSR | S_IWUSR, tab->nb_philo);
	tab->t_grab = sem_open("to_grab", O_CREAT, S_IRUSR | S_IWUSR, 1);
	tab->stop = sem_open("sem_stop", O_CREAT, S_IRUSR | S_IWUSR, 0);
	tab->sem_meals = sem_open("sem_meals", O_CREAT, S_IRUSR | S_IWUSR, 0);
}
