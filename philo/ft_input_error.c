/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:05:16 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/07 16:05:51 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_input_error(int argc)
{
	if (argc < 5)
	{
		printf("\033[31mToo few args\n");
		return (1);
	}
	if (argc > 6)
	{
		printf("\033[31mToo much args\n");
		return (1);
	}
	return (0);
}
