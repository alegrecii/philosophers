/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:31:02 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/24 19:09:24 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mega_free(t_tab *tab)
{
	free(tab->printer);
	free(tab->forks);
	free(tab->philos);
	free(tab->alive_lock);
	free(tab->t_eat_lock);
}
