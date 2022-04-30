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
		pthread_create(sim->philos[i].thread, NULL, &run_philo, arg);
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
	while (1)
	{
		pthread_mutex_lock(&a->sim->fork_lock);
		if (a->sim->dead_philo)
		{
			pthread_mutex_unlock(&a->sim->fork_lock);
			break ;
		}
		pthread_mutex_unlock(&a->sim->fork_lock);
		if (a->philo->state == NONE || a->philo->state == SLEEPING)
			eat(a->philo, a->sim, &break_loop);
		else if (a->philo->state == EATING)
			think(a->philo, a->sim, &break_loop);
		else if (a->philo->state == THINKING)
			sleep(a->philo, a->sim, &break_loop);
		if (break_loop)
			break ;
	}
	return (free(a), NULL);
}

void	eat(t_philo *philo, t_simululation *sim, int *b)
{
	usleep(sim->time_to_eat);
}

void	think(t_philo *philo, t_simululation *sim, int *b)
{
	usleep(sim->time_to_die);
}

void	sleep(t_philo *philo, t_simululation *sim, int *b)
{
	prinf("%d %d is sleeping\n", gettimeofday(), philo->id);
	usleep(sim->time_to_sleep);
}	

