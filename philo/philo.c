/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:05:05 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/24 16:27:15 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ho iniziato 3 Feb 12:48

void	simulation_starter(t_tab *tab)
{
	int		i;
	long	ftime;

	i = tab->nb_philo - 1;
	while (i >= 0)
	{
		pthread_create(\
		&tab->philos[i].life, NULL, life_manager, (void *) &tab->philos[i]);
		i--;
	}
	pthread_create(&tab->killer, NULL, killer, tab);
	pthread_join(tab->killer, NULL);
	i = tab->nb_philo - 1;
	ftime = ft_time();
	while (i >= 0 && tab->nb_philo != 1)
	{
		pthread_join(tab->philos[i].life, NULL);
		i--;
	}
	if (tab->killed == 0)
		printf("\033[1m\033[33m %ld \033[1m\033[35m MAX MEALS REACHED\n", \
		ftime - tab->start_time);
}

t_philo	philo_init(t_tab *tab, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.alive = 1;
	philo.last_eat = ft_time();
	philo.meals = 0;
	philo.tt_die = tab->tt_die;
	philo.tt_sleep = tab->tt_sleep;
	philo.tt_eat = tab->tt_eat;
	philo.nb_philo = tab->nb_philo;
	philo.start_time = tab->start_time;
	philo.alive_lock = &tab->alive_lock[id];
	philo.left_fork = &tab->forks[id];
	philo.right_fork = &tab->forks[(id + 1) % tab->nb_philo];
	philo.printer = tab->printer;
	philo.t_eat_lock = tab->t_eat_lock;
	return (philo);
}

void	mutex_init(t_tab *tab, int n)
{
	int	i;

	tab->forks = malloc(sizeof(pthread_mutex_t) * n);
	tab->alive_lock = malloc(sizeof(pthread_mutex_t) * n);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&tab->forks[i], NULL);
		pthread_mutex_init(&tab->alive_lock[i], NULL);
		i++;
	}
	tab->printer = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(tab->printer, NULL);
	tab->t_eat_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(tab->t_eat_lock, NULL);
}

int	tab_init(int argc, char **argv, t_tab *tab)
{
	int	i;

	i = 0;
	tab->nb_philo = ft_atoi(argv[1]);
	tab->tt_die = ft_atoi(argv[2]);
	tab->tt_eat = ft_atoi(argv[3]);
	tab->tt_sleep = ft_atoi(argv[4]);
	tab->start_time = ft_time();
	tab->killed = 0;
	if (argc == 6)
		tab->max_eat = ft_atoi(argv[5]);
	else
		tab->max_eat = -1;
	mutex_init(tab, tab->nb_philo);
	tab->philos = malloc(sizeof(t_philo) * tab->nb_philo);
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
			simulation_starter(&tab);
		else
			printf("\033[1m\033[33m %d \033[1m\033[31m 1 DIED \n", tab.tt_die);
		mega_free(&tab);
	}
	return (0);
}
