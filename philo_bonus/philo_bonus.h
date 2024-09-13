/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:15:49 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/13 12:49:57 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pthread.h>

typedef struct s_philo
{
	int			id;
	int			nb_philo;
	time_t		last_eat;
	int			alive;
	time_t		tt_die;
	time_t		tt_eat;
	time_t		tt_sleep;
	int			max_eat;
	int			meals;
	time_t		start_time;
	sem_t		*dead_check;
	sem_t		*grab;
	sem_t		*alive_sem;
	sem_t		*sem_meals;
	sem_t		*sem_print;
}	t_philo;

typedef struct s_tab
{
	pthread_t		killer;
	pthread_t		meal_check;
	int				nb_philo;
	time_t			tt_die;
	time_t			tt_eat;
	time_t			tt_sleep;
	int				max_eat;
	time_t			start_time;
	int				*killed;
	int				*free_forks;
	t_philo			*this_philo;
	t_philo			**philos;
	pid_t			**pids;
	sem_t			*t_grab;
	sem_t			*forks;
	sem_t			*stop;
	sem_t			*sem_meals;
	sem_t			*sem_print;
}	t_tab;

void	*meal_checker(void	*args);
void	sim_stopper(t_tab *tab);
int		alive_check(t_philo *p);
void	personal_sem_init(t_philo *p);
void	*killer(void *args);
void	pid_init(pid_t **p, int nb);
void	ft_msleep(time_t ms);
int		ft_input_error(int argc);
int		ft_atoi(const char *str);
time_t	ft_time(void);
void	ft_life(t_tab *tab);
void	ft_mega_free(t_tab *tab);
void	ft_waiter(t_tab *tab);
void	ft_sem_init(t_tab *tab);
void	ft_variables_init(t_tab *tab, char **argv);

#endif
