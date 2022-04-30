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

t_philo	*init_philo(int nbr_philo)
{
	int		i;
	t_philo	*philos;
	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * nbr_philo);
	while (++i < nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].state = NONE;
		philos[i].fork_left = 0;
		philos[i].fork_right = 0;
		philos[i].last_meal = 0;
		philos[i].nb_times_eat = 0;
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
	sim->philos = init_philo(sim->nb_philos);
	i = -1;
	sim->forks = (int *)malloc(sizeof(int) * sim->nb_philos);
	while (++i < sim->nb_philos)
		sim->forks[i] = 1;
	if (pthread_mutex_init(&sim->fork_lock, NULL))
		return (printf("philo mutex init failed\n"), NULL);
	return (sim);
}

void	free_sim(t_simululation *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nb_philos)
	{
		free(sim->philos[i].thread);
	}
	free(sim->philos);
	free(sim->forks);
	pthread_mutex_destroy(&sim->fork_lock);
	free(sim);
}