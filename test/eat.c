/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:20:31 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/11 08:17:42 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->lfork))
	{
		philo->error = 0;
		return (1);
	}
	print_line(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->rfork))
	{
		philo->error = 0;
		return (1);
	}
	print_line(philo, "has taken a fork");
	return (0);
}
int leave_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->lfork))
	{
		philo->error = 0;
		return (1);
	}
	if (pthread_mutex_unlock(philo->rfork))
	{
		philo->error = 0;
		return (1);
	}
	return (0);
}

int eat(t_philo *philo)
{
	if (take_fork(philo))
		return (1);
	print_line(philo, "is eating");
	pthread_mutex_lock(&(philo->data));
	philo->nb_times_eat++;
	philo->last_meal = getime();
	pthread_mutex_unlock(&(philo->data));
	ft_sleep(philo->sim->time_to_eat, philo->sim->nb_philo);
	if (leave_fork(philo))
		return (1);
	return (0);
}
