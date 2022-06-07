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

t_sim *init_sim(int argc, char **argv)
{
	t_sim *sim;
	int i;

	if (!(sim = (t_sim *)malloc(sizeof(t_sim))))
		return (NULL);
	sim->nbr_philo = ft_atoi(argv[1]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->dead_philo = 0;
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

t_philo *init_philo(int nbr_philo, t_sim *sim)
{
	int i;
	t_philo *philos;

	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * nbr_philo);
	while (++i < nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].sim = sim;
		philos[i].last_meal = 0;
		philos[i].nb_times_eat = 0;
		philos[i].fork_left = sim->forks + i;
		philos[i].fork_right = sim->forks + (i + 1) % nbr_philo;
		philos[i].nbr_forks = 0;
	}
	if (nbr_philo == 1)
		philos[0].fork_right = NULL;
	sim->time_start = gettime(sim);
	return (philos);
}

int print_line(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->sim->dead));
	if (philo->sim->dead_philo)
		return (pthread_mutex_unlock(&(philo->sim->dead)), 1);
	printf("\033[0;34m%d\033[0;32mms\t\033[0;33m%d\t\033[0;36m%s\n", gettime(philo->sim), philo->id, str);
	pthread_mutex_unlock(&(philo->sim->dead));
	return (0);
}

void eat(t_philo *philo)
{
	int forks;

	forks = 0;
	pthread_mutex_lock(philo->fork_left);
	print_line(philo, "has a fork");
	forks++;
	pthread_mutex_lock(&philo->sim->dead);
	while (philo->sim->dead_philo == 0 && forks < 2)
	{
		pthread_mutex_unlock(&philo->sim->dead);
		if (philo->fork_right)
		{
			pthread_mutex_lock(philo->fork_right);
			print_line(philo, "has a fork");
			forks++;
		}
		// usleep(philo->sim->time_to_die * 500);
		printf("in loop {%d}\n", philo->sim->dead_philo);
		pthread_mutex_lock(&philo->sim->dead);
	}
	pthread_mutex_unlock(&philo->sim->dead);
	if (forks == 2 && !print_line(philo, "is eating"))
	{
		philo->nb_times_eat++;
		usleep(philo->sim->time_to_eat * 1000);
		philo->last_meal = gettime(philo->sim);
	}
	if (philo->fork_right)
		pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	philo->nbr_forks = forks;
}

void *run(void *arg)
{
	pthread_mutex_lock(&(((t_philo *)arg)->sim->dead));
	while (((t_philo *)arg)->sim->dead_philo == 0 &&
		   ((t_philo *)arg)->sim->nbr_times_eat != ((t_philo *)arg)->nb_times_eat)
	{
		pthread_mutex_unlock(&(((t_philo *)arg)->sim->dead));
		eat(arg);
		if (!print_line(arg, "is sleeping"))
			usleep(((t_philo *)arg)->sim->time_to_sleep * 1000);
		print_line(arg, "is thinking");
		pthread_mutex_lock(&(((t_philo *)arg)->sim->dead));
	}
	pthread_mutex_unlock(&(((t_philo *)arg)->sim->dead));
	return (NULL);
}

void start(t_philo *philo)
{
	int i;
	int nbr_philo;

	nbr_philo = philo->sim->nbr_philo;
	i = -1;
	while (++i < nbr_philo)
	{
		philo[i].last_meal = philo[i].sim->time_start;
		pthread_create(&((philo + i)->thread), NULL, run, (philo + i));
		// usleep(1);
	}
}

void end(t_philo *philo)
{
	int i;
	int nbr_philo;

	nbr_philo = philo->sim->nbr_philo;
	i = -1;
	while (++i < nbr_philo)
	{
		pthread_join(((philo + i)->thread), NULL);
		pthread_mutex_destroy(((philo + i)->fork_left));
	}
	free(philo->sim->forks);
	pthread_mutex_destroy(&(philo->sim->dead));
	free(philo->sim);
	free(philo);
}
