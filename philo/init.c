/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:01:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/15 01:41:48 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_sim	*init_sim(int argc, char **argv)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (NULL);
	sim->nb_philo = ft_atoi(argv[1]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_start = getime();
	if (argc == 6)
		sim->nbr_times_eat = ft_atoi(argv[5]);
	else
		sim->nbr_times_eat = -1;
	sim->end = 1;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philo);
	if (!sim->forks)
		return (free(sim), NULL);
	i = -1;
	while (++i < sim->nb_philo)
		pthread_mutex_init(&(sim->forks[i]), NULL);
	pthread_mutex_init(&sim->dead, NULL);
	pthread_mutex_init(&sim->data, NULL);
	return (sim);
}

t_philo	*init_philo(int nbr_philo, t_sim *sim)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * nbr_philo);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].sim = sim;
		philo[i].lfork = sim->forks + i;
		philo[i].rfork = sim->forks + (i + 1) % nbr_philo;
		philo[i].nb_times_eat = 0;
		philo[i].error = 1;
		philo[i].all = philo;
	}
	return (philo);
}
