/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:52:33 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/15 02:00:53 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	getime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(int time, int nbr_philo)
{
	size_t	i;

	i = getime();
	while (getime() - i < (size_t)time)
	{
		if (nbr_philo <= 100)
			usleep(100);
		else
			usleep(1000);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		++i;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + str[i++] - '0';
	return (sign * nbr);
}

int	print_line(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(&(philo->sim->dead)))
		return (1);
	printf("%d\t%d\t %s\n", getime() - philo->sim->time_start, philo->id, str);
	return (pthread_mutex_unlock(&(philo->sim->dead)), 0);
}

void	destroy_mutexs(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		pthread_mutex_destroy((philo[i].lfork));
	}
	pthread_mutex_destroy(&(philo->sim->dead));
	pthread_mutex_destroy(&(philo->sim->data));
}
