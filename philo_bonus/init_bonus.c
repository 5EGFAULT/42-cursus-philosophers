/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:01:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/15 22:31:01 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_sim	*init_sim(int argc, char **argv)
{
	t_sim	*sim;

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
	sem_unlink("/dead_sem");
	sem_unlink("/fork_sem");
	sim->dead = sem_open("/dead_sem", O_CREAT, 0644, 1);
	sim->forks = sem_open("/fork_sem", O_CREAT, 0644, sim->nb_philo);
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
		philo[i].nb_times_eat = 0;
	}
	return (philo);
}
