/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:11:41 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/13 12:50:44 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total;
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	total = ft_strlen(s1) + ft_strlen(s2);
	s = (char *) malloc(sizeof(*s1) * (total +1));
	if (!s)
		return (NULL);
	while (s1[j] != '\0')
	{
		s[j] = s1[j];
		j++;
	}
	while (s2[i] != '\0')
	{
		s[j] = s2[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

static int	length(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = length(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	str[i] = '\0';
	i--;
	while (n > 9)
	{
		str[i] = (n % 10) + '0';
		i--;
		n /= 10;
	}
	str[i] = n + '0';
	return (str);
}

void	personal_sem_init(t_philo *p)
{
	char	*str;
	char	*str1;
	char	*str2;

	str = ft_itoa(p->id);
	str1 = ft_strjoin("sem_bin_d_", str);
	str2 = ft_strjoin("sem_bin_a_", str);
	sem_unlink(str1);
	sem_unlink(str2);
	p->dead_check = sem_open(str1, O_CREAT, S_IRUSR | S_IWUSR, 2);
	p->alive_sem = sem_open(str2, O_CREAT, S_IRUSR | S_IWUSR, 1);
	free(str);
	free(str1);
	free(str2);
}
