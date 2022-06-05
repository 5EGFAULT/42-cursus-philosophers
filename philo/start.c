/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:55:18 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 14:55:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_sim	*init_sim(int argc, char **argv)
{
	t_sim	*sim;
	int		i;

	if (!(sim = (t_sim *)malloc(sizeof(t_sim))))
		return (NULL);
	sim->nbr_philo = ft_atoi(argv[1]);
	sim->time_to_eat = ft_atoi(argv[2]);
	sim->time_to_sleep = ft_atoi(argv[3]);
	sim->time_to_die = ft_atoi(argv[4]);
	if (argc == 6)
		sim->nbr_times_eat = ft_atoi(argv[5]);
	else
		sim->nbr_times_eat = -1;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nbr_philo);
	i = -1;
	while (++i < sim->nbr_philo)
		pthread_mutex_init(sim->forks + i, NULL);
	sim->time_start = 0;
	pthread_mutex_init(&(sim->dead), NULL);
	return (sim);
}

t_philo	*init_philo(int nbr_philo, t_sim *sim)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * nbr_philo);
	while (++i < nbr_philo)
	{
		philos[i].id = i;
		philos[i].sim = sim;
		philos[i].last_meal = 0;
		philos[i].nb_times_eat = 0;
		philos[i].fork_left = sim->forks + i;
		philos[i].fork_right = sim->forks + (i + 1) % nbr_philo;
	}
	return (philos);
}

void	start(t_philo	*philo)
{
	int		i;
	int		nbr_philo;

	nbr_philo = philo->sim->nbr_philo;
	i = -1;
	while (++i < nbr_philo)
	{
		pthread_create(philo[i].thread, NULL, &(philo[i].thread), &philo[i]);
	}

}
