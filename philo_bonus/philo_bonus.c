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

#include "philo_bonus.h"

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
	return (0);
}

int	watch(t_philo *philo)
{
	while (1)
	{
		if (getime() - philo->last_meal >= philo->sim->time_to_die)
		{
			sem_wait(philo->sim->dead);
			printf("%d\t%d\t %s\n", getime() - philo->sim->time_start, \
			philo->id, "died");
			exit(1);
		}
		usleep(100);
	}
	return (0);
}
