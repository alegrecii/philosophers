/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:15:49 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/24 16:35:45 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t		life;
	int				id;
	int				nb_philo;
	int				last_eat;
	int				alive;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_eat;
	int				meals;
	long int		start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*t_eat_lock;
	pthread_mutex_t	*alive_lock;
}	t_philo;

typedef struct s_tab
{
	pthread_t		killer;
	int				nb_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_eat;
	long int		start_time;
	int				killed;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*alive_lock;
	pthread_mutex_t	*t_eat_lock;
	t_philo			*philos;

}	t_tab;

int		alive_check(t_philo *p);
void	*life_manager(void *philo);
void	mega_free(t_tab *tab);
void	*killer(void *args);
void	ft_msleep(long ms);
void	simulation_starter(t_tab *tab);
int		ft_input_error(int argc);
int		ft_atoi(const char *str);
int		ft_time(void);

#endif
