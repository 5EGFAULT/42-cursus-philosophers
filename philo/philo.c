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
	philos = init_philo(sim->nbr_philo, sim);
	if (!philos)
		return (3);
	start(philos);
	watch(sim, philos);
	end(philos);
	return (0);
}

void watch(t_sim *sim, t_philo *philo)
{
	int i;

	while (sim->nbr_philo != 1)
	{
		i = -1;
		while (++i < sim->nbr_philo)
		{
			if (philo->sim->time_to_die <
					gettime(philo->sim) - philo[i].last_meal &&
				philo[i].nb_times_eat != philo->sim->nbr_times_eat)
			{
				pthread_mutex_lock(&(philo->sim->dead));
				philo->sim->dead_philo = philo[i].id;
				printf("\033[0;34m%d\t\033[0;33m%d\t\033[0;31mdied\n", gettime(philo->sim), philo[i].id);
				pthread_mutex_unlock(&(philo->sim->dead));
				return;
			}
			else if (check_meals(sim, philo))
				return;
		}
	}
}

int check_meals(t_sim *sim, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < sim->nbr_philo)
	{
		// printf("{%d}{%d}", philo[i].nb_times_eat, sim->nbr_times_eat);
		if (philo[i].nb_times_eat == sim->nbr_times_eat)
			return (1);
	}
	return (0);
}