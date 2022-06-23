/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:24:13 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 11:24:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim	*sim;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (printf("philo params error.\nUsage: ./philo \
<number of philosophers> <time to eat> <time to sleep> <time to die> \
[number of times each philosopher must eat]\n"), 2);
	if (!check_arg(argc, argv))
		return (2);
	sim = init_sim(argc, argv);
	if (!sim)
		return (3);
	philos = init_philo(sim->nb_philo, sim);
	if (!philos)
		return (3);
	start(philos);
	watch(philos);
	return (0);
}

int	check_death(t_philo *philo, t_philo *p)
{
	int	r;

	r = 0;
	pthread_mutex_lock(&philo->sim->data);
	if (getime() - philo->last_meal >= philo->sim->time_to_die && \
	philo->nb_times_eat != philo->sim->nbr_times_eat)
	{
		pthread_mutex_lock(&philo->sim->dead);
		philo->sim->end = 0;
		printf("%d\t%d\t %s\n", getime() - philo->sim->time_start, \
		philo->id, "died");
		r = 1;
		destroy_mutexs(p);
	}
	pthread_mutex_unlock(&philo->sim->data);
	return (r);
}

int	check_all_eaten(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philo[0].sim->data);
	while (++i < philo->sim->nb_philo)
	{
		if (philo[i].nb_times_eat < philo->sim->nbr_times_eat || \
		philo->sim->nbr_times_eat == -1)
			return (pthread_mutex_unlock(&philo[i].sim->data), 1);
	}
	pthread_mutex_unlock(&philo[0].sim->data);
	destroy_mutexs(philo);
	return (0);
}

int	watch(t_philo *philo)
{
	int	i;

	while (check_all_eaten(philo))
	{
		i = -1;
		while (++i < philo->sim->nb_philo)
		{
			if (check_death(philo + i, philo))
				return (1);
			else if (!check_all_eaten(philo))
				return (1);
		}
	}
	return (0);
}
