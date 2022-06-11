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

int main(int argc, char **argv)
{
	t_sim *sim;
	t_philo *philos;

	if (argc < 5 || argc > 6)
		return (printf("philo params error.\nUsage: ./philo \
<number of philosophers> <time to eat> <time to sleep> <time to die> \
[number of times each philosopher must eat]\n"),
				2);
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
	end(philos);
	return (0);
}

int check_death(t_philo *philo)
{
	int r;

	r = 0;
	pthread_mutex_lock(&philo->data);
	if (philo->nb_times_eat != philo->sim->nbr_times_eat && philo->last_meal + philo->sim->time_to_die < getime())
	{
		pthread_mutex_lock(&philo->sim->dead);
		philo->sim->end = 0;
		printf("%d\t%d\t %s\n", getime() - philo->sim->time_start, philo->id, "died");
		r = 1;
		pthread_mutex_unlock(&philo->sim->dead);
	}
	pthread_mutex_unlock(&philo->data);
	return (r);
}

int check_all_eaten(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->sim->nb_philo)
	{
		pthread_mutex_lock(&philo[i].data);
		if (philo[i].nb_times_eat != philo->sim->nbr_times_eat)
			return (pthread_mutex_unlock(&philo[i].data), 1);
		pthread_mutex_unlock(&philo[i].data);
	}
	return (0);
}
void watch(t_philo *philo)
{
	int i;

	while (check_all_eaten(philo))
	{
		i = -1;
		while (++i < philo->sim->nb_philo)
		{
			if (check_death(philo + i))
				return;
		}
	}
}
