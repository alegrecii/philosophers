/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:05:05 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/13 12:51:30 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// ho iniziato 3 Feb 12:48

void	simulation_starter(t_tab *tab)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < tab->nb_philo)
	{
		pid = fork();
		if (pid > 0)
			*tab->pids[i] = pid;
		else if (pid == 0)
		{
			tab->this_philo = tab->philos[i];
			ft_life(tab);
		}
		i++;
	}
	if (tab->max_eat != -1)
		pthread_create(&tab->meal_check, NULL, meal_checker, tab);
	sem_wait(tab->stop);
	if (pid == 0)
		ft_mega_free(tab);
	if (pid > 0)
		sim_stopper(tab);
	ft_waiter(tab);
}

t_philo	*philo_init(t_tab *tab, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = id;
	philo->alive = 1;
	philo->last_eat = ft_time();
	philo->meals = 0;
	philo->tt_die = tab->tt_die;
	philo->tt_sleep = tab->tt_sleep;
	philo->tt_eat = tab->tt_eat;
	philo->nb_philo = tab->nb_philo;
	philo->start_time = tab->start_time;
	philo->grab = tab->t_grab;
	philo->sem_meals = tab->sem_meals;
	philo->max_eat = tab->max_eat;
	philo->sem_print = tab->sem_print;
	return (philo);
}

int	tab_init(int argc, char **argv, t_tab *tab)
{
	int	i;

	i = 0;
	ft_variables_init(tab, argv);
	ft_sem_init(tab);
	tab->pids = malloc(sizeof(pid_t *) * tab->nb_philo);
	pid_init(tab->pids, tab->nb_philo);
	tab->philos = malloc(sizeof(t_philo *) * tab->nb_philo);
	if (argc == 6)
		tab->max_eat = ft_atoi(argv[5]);
	else
		tab->max_eat = -1;
	while (i < tab->nb_philo)
	{
		tab->philos[i] = philo_init(tab, i);
		i++;
	}
	if (tab->nb_philo < 1 || tab->tt_die < 0 || tab->tt_eat < 0
		|| tab->tt_sleep < 0 || (tab->max_eat < 0 && tab->max_eat != -1))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_tab	tab;
	int		error;

	error = 0;
	if (argc != 5 && argc != 6)
		return (ft_input_error(argc));
	else
		error = tab_init(argc, argv, &tab);
	if (!error)
	{
		if (tab.nb_philo > 1)
		{
			simulation_starter(&tab);
		}
		else
			printf("\033[1m\033[33m %ld \033[1m\033[31m 1 DIED \n", tab.tt_die);
		ft_mega_free(&tab);
	}
	return (0);
}
