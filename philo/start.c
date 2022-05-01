/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:55:18 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 14:55:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sim(t_simululation *sim)
{
	int				i;
	t_arg			*arg;

	i = -1;
	while (++i < sim->nb_philos)
	{
		arg = (t_arg *)malloc(sizeof(t_arg));
		if (!arg)
			return ;
		arg->philo = &(sim->philos[i]);
		arg->sim = sim;
		pthread_create(sim->philos[i].thread, NULL, &run_philo, (void *)arg);
	}
	i = -1;
	while (++i < sim->nb_philos)
		pthread_join(*(sim->philos[i].thread), NULL);
}

void	*run_philo(void *arg)
{
	t_arg			*a;
	int				break_loop;
	a = (t_arg *)arg;
	break_loop = 0;
	gettimeofday(a->sim->tv, a->sim->tz);
	a->philo->last_meal = a->sim->tv->tv_usec;
	while (1)
	{
		if (a->philo->state == SLEEPING)
			break_loop =  philo_eat(a->philo, a->sim);
		else if (a->philo->state == EATING)
		{
			pthread_mutex_lock(&(a->sim->dead_lock));
			if (a->sim->dead_philo)
			{
				pthread_mutex_unlock(&(a->sim->dead_lock));
				break ;
			}
			gettimeofday(a->sim->tv, a->sim->tz);
			printf("%ld %d is thinking\n",a->sim->tv->tv_usec, a->philo->id);
			a->philo->state = THINKING;
			pthread_mutex_unlock(&(a->sim->dead_lock));
		}
		else if (a->philo->state == THINKING)
		{
			pthread_mutex_lock(&(a->sim->dead_lock));
			if (a->sim->dead_philo)
			{
				pthread_mutex_unlock(&(a->sim->dead_lock));
				break ;
			}
			gettimeofday(a->sim->tv, a->sim->tz);
			printf("%ld %d is sleeping\n",a->sim->tv->tv_usec, a->philo->id);
			a->philo->state = SLEEPING;
			pthread_mutex_unlock(&(a->sim->dead_lock));
			usleep(a->sim->time_to_sleep);
		}
		//	philo_think(a->philo, a->sim, &break_loop);
		//else if (a->philo->state == THINKING)
		//	philo_sleep(a->philo, a->sim, &break_loop);
		if (break_loop)
			break ;
	}
	pthread_mutex_unlock(&(a->sim->dead_lock));
	return (free(a), NULL);
}

int	sim_check_dead(t_simululation *sim)
{
	int				i;

	i = 0;
	pthread_mutex_lock(&(sim->dead_lock));
	if (sim->dead_philo)
		i = 1;
	pthread_mutex_unlock(&(sim->dead_lock));
	return (i);
}

int	is_philo_dead(t_philo *philo, t_simululation *sim)
{
	gettimeofday(sim->tv, sim->tz);
	if (sim->tv->tv_usec - philo->last_meal > sim->time_to_die)
	{
		pthread_mutex_lock(&sim->dead_lock);
		sim->dead_philo = philo->id;
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d has died\n", sim->tv->tv_usec, philo->id);
		memset(sim->forks, 0, sizeof(int) * sim->nb_philos);
		pthread_mutex_unlock(&sim->dead_lock);
		return (1);
	}
	return (0);
}
