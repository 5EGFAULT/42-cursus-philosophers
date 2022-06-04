 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:21:04 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 13:21:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int nbr_philo, t_simululation *sim)
{
	int		i;
	t_philo	*philos;
	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * nbr_philo);
	while (++i < nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].state = SLEEPING;
		philos[i].fork_left = 0;
		philos[i].fork_right = 0;
		gettimeofday(sim->tv, sim->tz);
		philos[i].last_meal = sim->tv->tv_usec;
		philos[i].nb_times_eat = 0;
		philos[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
	}
	return (philos);
}

t_simululation	*init_sim(int argc, char **argv)
{
	t_simululation	*sim;
	int				i;

	sim = (t_simululation *)malloc(sizeof(t_simululation));
	if (!sim)
		return (NULL);
	sim->nb_philos = ft_atoi(argv[1]);
	sim->time_to_eat = ft_atoi(argv[2]);
	sim->time_to_sleep = ft_atoi(argv[3]);
	sim->time_to_die = ft_atoi(argv[4]);
	if (argc == 6)
		sim->nb_times_to_eat = ft_atoi(argv[5]);
	else
		sim->nb_times_to_eat = -1;
	sim->dead_philo = 0;
	sim->tv = malloc(sizeof(struct timeval));
	sim->tz = malloc(sizeof(struct timezone));
	sim->philos = init_philo(sim->nb_philos, sim);
	i = -1;
	sim->forks = (int *)malloc(sizeof(int) * sim->nb_philos);
	while (++i < sim->nb_philos)
		if (pthread_mutex_init(sim->forks + i, NULL));
			return (printf("philo mutex init failed\n"), NULL);
	if (pthread_mutex_init(&sim->dead_lock, NULL))
		return (printf("philo mutex init failed\n"), NULL);
	return (sim);
}

void	free_sim(t_simululation *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nb_philos)
		pthread_mutex_destroy(sim->forks + i);
	i = -1;
	while (++i < sim->nb_philos)
		free(sim->philos[i].thread);
	free(sim->philos);
	free(sim->forks);
	pthread_mutex_destroy(&sim->dead_lock);
	free(sim);
}