/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:09:06 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/09 22:16:53 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philo *philo)
{
	int r;
	pthread_mutex_lock(&((t_philo *)philo)->sim->dead);
	r = ((t_philo *)philo)->sim->end;
	pthread_mutex_unlock(&((t_philo *)philo)->sim->dead);
	return (r);
}

void *run(void *philo)
{
	t_philo *p = (t_philo *)philo;

	printf("%d %d is alive\n", getime() - p->sim->time_start, p->id);
	pthread_mutex_lock(p->lfork);
	printf("%d %d  lock left f\n", getime() - p->sim->time_start, p->id);
	pthread_mutex_lock(p->rfork);
	printf("%d %d  lock right f\n", getime() - p->sim->time_start, p->id);
	ft_sleep(400);
	pthread_mutex_unlock(p->lfork);
	printf("%d %d unlock left f\n", getime() - p->sim->time_start, p->id);
	pthread_mutex_unlock(p->rfork);
	printf("%d %d unlock right f\n", getime() - p->sim->time_start, p->id);
	printf("%d %d is dead\n", getime() - p->sim->time_start, p->id);
	// eat(philo);
	//  while (is_dead(philo) && ((t_philo *)philo)->error &&
	//	   ((t_philo *)philo)->sim->nbr_times_eat != ((t_philo *)philo)->nb_times_eat)
	//{
	//	// eat(philo);
	//	//  if (!print_line(philo, "is sleeping"))
	//	//	ft_sleep(((t_philo *)philo)->sim->time_to_sleep);
	//	//  print_line(philo, "is thinking");
	//	//  printf("%d OUT\n", ((t_philo *)philo)->id);
	//}
	return (NULL);
}

void start(t_philo *philo)
{
	int i;

	i = -1;
	philo->sim->time_start = getime();
	while (++i < philo->sim->nb_philo)
	{
		pthread_create(&(philo[i].thread), NULL, run, philo + i);
		usleep(100);
	}
}

void end(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		pthread_mutex_destroy((philo[i].lfork));
		pthread_mutex_destroy(&(philo[i].data));
	}
	// pthread_mutex_destroy(&(philo->sim->data));
	pthread_mutex_destroy(&(philo->sim->dead));
	i = -1;
	while (++i < philo->sim->nb_philo)
		pthread_join(philo[i].thread, NULL);
	free(philo->sim->forks);
	free(philo->sim);
	free(philo);
}