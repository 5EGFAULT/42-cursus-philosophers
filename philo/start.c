/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:09:06 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/15 01:56:44 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
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

int	is_eaten(t_philo *philo)
{
	int	r;

	if (pthread_mutex_lock(&((t_philo *)philo)->sim->data))
		return (0);
	if (philo->nb_times_eat != philo->sim->nbr_times_eat)
		r = 1;
	else
		r = 0;
	pthread_mutex_unlock(&((t_philo *)philo)->sim->data);
	return (r);
}

void	*run(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		usleep(1000);
	while (is_dead(p) && is_eaten(p))
	{
		if (eat(p))
			return (NULL);
		if (print_line(p, "is sleeping"))
			return (NULL);
		else
			ft_sleep(p->sim->time_to_sleep, p->sim->nb_philo);
		if (print_line(p, "is thinking"))
			return (NULL);
	}
	return (NULL);
}

void	start(t_philo *philo)
{
	int	i;

	philo->sim->time_start = getime();
	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		philo[i].last_meal = philo->sim->time_start;
		pthread_create(&(philo[i].thread), NULL, &run, &philo[i]);
	}
}

void	end(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->sim->nb_philo)
		pthread_join(philo[i].thread, NULL);
	free(philo->sim->forks);
	free(philo->sim);
	free(philo);
}
