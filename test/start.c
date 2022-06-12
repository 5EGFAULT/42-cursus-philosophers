/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:09:06 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/12 04:40:58 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philo *philo)
{
	//(void)philo;
	// return (1);
	if (pthread_mutex_lock(&((t_philo *)philo)->sim->dead))
		return (0);
	if (((t_philo *)philo)->sim->end)
	{
		pthread_mutex_unlock(&((t_philo *)philo)->sim->dead);
		return (1);
	}
	pthread_mutex_unlock(&((t_philo *)philo)->sim->dead);
	return (0);
}

int is_eaten(t_philo *philo)
{
	//(void)philo;
	// return (1);
	int r;
	if (pthread_mutex_lock(&((t_philo *)philo)->sim->data))
		return (0);
	if (philo->nb_times_eat != philo->sim->nbr_times_eat)
		r = 1;
	else
		r = 0;
	if (pthread_mutex_unlock(&((t_philo *)philo)->sim->data))
		return (0);
	return (r);
}

void *run(void *philo)
{
	t_philo *p = (t_philo *)philo;
	while (is_dead(p))
	{
		if (eat(p))
			return (printf("  %d  eat  error\n", p->id), NULL);
		if (print_line(p, "is sleeping"))
			return (printf("  %d  sleep  error\n", p->id), NULL);
		else
			ft_sleep(p->sim->time_to_sleep, p->sim->nb_philo);
		if (print_line(p, "is thinking"))
			return (printf("  %d   think error\n", p->id), NULL);
	}
	return (printf("  %d   dead error\n", p->id), NULL);
}

void start(t_philo *philo)
{
	int i;

	philo->sim->time_start = getime();
	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		if (i % 2 == 0 && (philo->sim->nb_philo - 1) != i)
		// if (i % 2 == 0)
		{
			philo[i].last_meal = philo->sim->time_start;
			pthread_create(&(philo[i].thread), NULL, &run, &philo[i]);
		}
	}
	// usleep(100);

	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		if (i % 2)
		{
			philo[i].last_meal = philo->sim->time_start;
			pthread_create(&(philo[i].thread), NULL, &run, &philo[i]);
		}
	}
	if ((philo->sim->nb_philo - 1) % 2 == 0)
	{
		philo[i].last_meal = philo->sim->time_start;
		pthread_create(&(philo[philo->sim->nb_philo - 1].thread), NULL, run,
					   philo + philo->sim->nb_philo - 1);
	} // usleep(100);
}

void destroy_mutexs(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		pthread_mutex_destroy((philo[i].lfork));
		// pthread_mutex_destroy(&(philo[i].data));
	}
	pthread_mutex_destroy(&(philo->sim->dead));
	pthread_mutex_destroy(&(philo->sim->data));
}

void end(t_philo *philo)
{
	int i;

	// i = -1;
	//  while (++i < philo->sim->nb_philo)
	//{
	//	pthread_mutex_destroy((philo[i].lfork));
	//	pthread_mutex_destroy(&(philo[i].data));
	//  }
	//// pthread_mutex_destroy(&(philo->sim->data));
	// pthread_mutex_destroy(&(philo->sim->dead));
	destroy_mutexs(philo);
	i = -1;
	while (++i < philo->sim->nb_philo)
		pthread_join(philo[i].thread, NULL);
	free(philo->sim->forks);
	free(philo->sim);
	free(philo);
}
