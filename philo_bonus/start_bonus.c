/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:09:06 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/15 11:27:23 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int is_eaten(t_philo *philo)
{
	if (philo->nb_times_eat != philo->sim->nbr_times_eat)
		return (1);
	else
		return (0);
}

void *run(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	while (is_eaten(p))
	{
		eat(p);
		print_line(p, "is sleeping");
		ft_sleep(p->sim->time_to_sleep, p->sim->nb_philo);
		print_line(p, "is thinking");
	}
	return (NULL);
}

void start(t_philo *philo)
{
	int i;
	int status;
	int k;

	philo->sim->time_start = getime();
	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		philo[i].last_meal = philo->sim->time_start;
		philo[i].p_id = fork();
		if (philo[i].p_id == 0)
		{
			philo[i].sim->dead = sem_open("../dead_sem", O_RDONLY);
			philo[i].sim->forks = sem_open("../fork_sem", O_RDONLY);
			pthread_create(&(philo[i].thread), NULL, &run, philo + i);
			watch(philo + i);
		}
	}
	i = -1;
	k = 0;
	while (++i < philo->sim->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 256)
		{
			k = 1;
			break;
		}
	}
	if (k)
	{
		i = -1;
		while (++i < philo->sim->nb_philo)
			kill(philo[i].p_id, SIGKILL);
	}
	sem_unlink("../dead_sem");
	sem_unlink("../fork_sem");
}
