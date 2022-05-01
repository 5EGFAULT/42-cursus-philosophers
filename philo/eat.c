/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 05:14:47 by marvin            #+#    #+#             */
/*   Updated: 2022/05/01 05:14:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo, t_simululation *sim)
{
	pthread_mutex_lock(&(sim->dead_lock));
	if (sim->dead_philo)
		return (1);
	gettimeofday(sim->tv, sim->tz);
	if (sim->tv->tv_usec - philo->last_meal > sim->time_to_die)
	{
		sim->dead_philo = philo->id;
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d has died\n", sim->tv->tv_usec, philo->id);
		memset(sim->forks, 0, sizeof(int) * sim->nb_philos);
		return (1);
	}
	pthread_mutex_unlock(&(sim->dead_lock));
	while (!philo->fork_left || !philo->fork_right)
	{
		pthread_mutex_lock(&sim->fork_lock);
		if (!philo->fork_left && philo_take_left_fork(philo, sim))
		{
			pthread_mutex_unlock(&sim->fork_lock);
			return (1);
		}
		if (!philo->fork_right && philo_take_right_fork(philo, sim))
		{
			pthread_mutex_unlock(&sim->fork_lock);
			return (1);
		}
		pthread_mutex_unlock(&sim->fork_lock);
	}
	philo->state = EATING;
	gettimeofday(sim->tv, sim->tz);
	printf("%ld %d is eating\n", sim->tv->tv_usec, philo->id);
	usleep(sim->time_to_eat);
	gettimeofday(sim->tv, sim->tz);
	philo->last_meal = sim->tv->tv_usec;
	philo->fork_left = 0;
	philo->fork_right = 0;
	pthread_mutex_lock(&sim->fork_lock);
	if (philo->id == sim->nb_philos || philo->id == 1)
	{
			sim->forks[sim->nb_philos - 1] = 1;
			sim->forks[0] = 1;
	}
	else
	{
		sim->forks[philo->id - 1] = 1;
		sim->forks[philo->id] = 1;
	}
	pthread_mutex_unlock(&sim->fork_lock);
	return (0);
}

int	philo_take_left_fork(t_philo *philo, t_simululation *sim)
{
	if (philo->id > 1 && sim->forks[philo->id - 1])
	{
		philo->fork_left = 1;
		sim->forks[philo->id - 1] = 0;
	}
	else if (sim->forks[sim->nb_philos - 1])
	{
		philo->fork_left = 1;
		sim->forks[sim->nb_philos - 1] = 0;
	}
	if (philo->fork_left)
	{
		pthread_mutex_lock(&(sim->dead_lock));
		if (sim->dead_philo)
			return (1);
		pthread_mutex_unlock(&(sim->dead_lock));
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d is has taken a fork left\n", sim->tv->tv_usec, philo->id);
	}
	return (0);
}

int	philo_take_right_fork(t_philo *philo, t_simululation *sim)
{
	if (philo->id < sim->nb_philos && sim->forks[philo->id])
	{
		philo->fork_right = 1;
		sim->forks[philo->id - 1] = 0;
	}
	else if (sim->forks[0])
	{
		philo->fork_right = 1;
		sim->forks[0] = 0;
	}
	if (philo->fork_right)
	{
		pthread_mutex_lock(&(sim->dead_lock));
		if (sim->dead_philo)
			return (1);
		pthread_mutex_unlock(&(sim->dead_lock));
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d is has taken a fork right\n", sim->tv->tv_usec, philo->id);
	}
	return (0);
}