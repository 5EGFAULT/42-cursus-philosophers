/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:52:33 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/09 22:19:43 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int getime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_sleep(int time)
{
	size_t i;

	i = getime();
	usleep(time * 800);
	while (getime() - i < (size_t)time)
		usleep(100);
}

int ft_atoi(const char *str)
{
	int i;
	int nbr;
	int sign;

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

int print_line(t_philo *philo, char *str)
{
	// printf("==> %d %s  %d\n", philo->id, str, philo->sim->end);
	if (pthread_mutex_lock(&(philo->sim->dead)))
		return (1);
	if (!(philo->sim->end))
		return (pthread_mutex_unlock(&(philo->sim->dead)), 1);
	printf("%d\t%d\t%s\n", getime() - philo->sim->time_start, philo->id, str);
	pthread_mutex_unlock(&(philo->sim->dead));
	return (0);
}
