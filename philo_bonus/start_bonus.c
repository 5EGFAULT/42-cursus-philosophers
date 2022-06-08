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

#include "philo_bonus.h"

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
	// pthread_mutex_init(sim->forks + i, NULL);
	// pthread_mutex_init(&(sim->dead), NULL);
	// pthread_mutex_init(&(sim->data), NULL);
	sem_init(&(sim->forks), 1, sim->nbr_philo);
	sem_init(&(sim->dead), 1, 0);
	sem_init(&(sim->data), 1, 1);
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
		philos[i].lfork = 1;
		philos[i].rfork = &(philos[(i + 1) % nbr_philo].lfork);
		philos[i].is_eating = 0;
	}
	sim->time_start = gettime(sim);
	return (philos);
}

int print_line(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->sim->dead));
	if (philo->sim->dead_philo)
		return (pthread_mutex_unlock(&(philo->sim->dead)), 1);
	printf("\033[0;34m%d\t\033[0;33m%d\t\033[0;36m%s\n", gettime(philo->sim), philo->id, str);
	pthread_mutex_unlock(&(philo->sim->dead));
	return (0);
}

int check_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->sim->dead));
	if (philo->sim->dead_philo)
		return (pthread_mutex_unlock(&(philo->sim->dead)), 0);
	pthread_mutex_unlock(&(philo->sim->dead));
	return (1);
}

void eat(t_philo *philo)
{

	pthread_mutex_lock(philo->fork_left);
	print_line(philo, "has a fork");
	pthread_mutex_lock(philo->fork_right);
	print_line(philo, "has a fork");
	if (!print_line(philo, "is eating"))
	{
		pthread_mutex_lock(&philo->sim->data);
		philo->nb_times_eat++;
		philo->last_meal = gettime(philo->sim);
		pthread_mutex_unlock(&philo->sim->data);
		ft_sleep(philo->sim->time_to_eat);
	}
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void *run(void *arg)
{
	pthread_mutex_lock(&(((t_philo *)arg)->sim->dead));
	// while (((t_philo *)arg)->sim->dead_philo == 0)
	while (((t_philo *)arg)->sim->dead_philo == 0 &&
		   ((t_philo *)arg)->sim->nbr_times_eat != ((t_philo *)arg)->nb_times_eat)
	{
		pthread_mutex_unlock(&(((t_philo *)arg)->sim->dead));
		eat(arg);
		if (!print_line(arg, "is sleeping"))
			ft_sleep(((t_philo *)arg)->sim->time_to_sleep);
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
	if (nbr_philo == 1)
	{
		if (philo->sim->nbr_times_eat == 0)
			return;
		print_line(philo, "has a fork");
		ft_sleep(philo->sim->time_to_die);
		print_line(philo, "\033[0;31mdied");
		return;
	}
	while (++i < nbr_philo)
	{
		philo[i].last_meal = 0;
		pthread_create(&((philo + i)->thread), NULL, run, (philo + i));
		// ft_sleep(10);
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
	}
	sem_destroy(&(sim->forks);
	sem_destroy(&(sim->dead);
	sem_destroy(&(sim->data);
	free(philo->sim);
	free(philo);
}

void ft_sleep(int time)
{
	int timenow = getrealtime();
	while (timenow + time > getrealtime())
	{
		usleep(100);
	}
}

int getrealtime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
