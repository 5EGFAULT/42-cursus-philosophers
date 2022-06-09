/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:20:31 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/09 19:26:02 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_fork(t_philo *philo, int rl)
{
	printf("%d %d take\n", philo->id, rl);
	if (rl)
	{
		if (pthread_mutex_lock(philo->lfork))
		{
			philo->error = 0;
			return (1);
		}
		else
			return (print_line(philo, " has taken a fork"), 0);
	}
	else
	{
		if (philo->rfork && pthread_mutex_lock(philo->rfork))
		{
			if (philo->rfork)
				philo->error = 0;
			return (1);
		}
		else
			return (print_line(philo, " has taken a fork"), 0);
	}
}
int leave_fork(t_philo *philo, int rl)
{
	printf("%d %d leave\n", philo->id, rl);
	if (rl)
	{
		if (pthread_mutex_unlock(philo->lfork))
		{
			philo->error = 0;
			return (1);
		}
		else
			return (0);
	}
	else
	{
		if (philo->rfork && pthread_mutex_unlock(philo->rfork))
		{
			if (philo->rfork)
				philo->error = 0;
			return (1);
		}
		else
			return (0);
	}
}

int eat(t_philo *philo)
{
	if (take_fork(philo, 1))
		return (0);
	if (take_fork(philo, 0))
		return (0);
	printf("%d IN\n", philo->id);
	pthread_mutex_lock(&philo->data);
	philo->last_meal = getime();
	philo->nb_times_eat++;
	pthread_mutex_unlock(&philo->data);
	print_line(philo, " is eating");
	ft_sleep(philo->sim->time_to_eat);
	if (leave_fork(philo, 0))
		return (0);
	if (leave_fork(philo, 1))
		return (0);
	return (1);
}
