/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:21:06 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 11:21:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONNUS_H
#define PHILO_BONNUS_H
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_sim
{
	int nbr_philo;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int time_start;
	int nbr_times_eat;
	sem_t forks;
	sem_t dead;
	sem_t data;
	int dead_philo;
} t_sim;

typedef struct s_philo
{
	int id;
	int last_meal;
	int nb_times_eat;
	// pthread_t thread;
	t_sim *sim;
} t_philo;

int ft_atoi(const char *str);
t_philo *init_philo(int nbr_philo, t_sim *sim);
t_sim *init_sim(int argc, char **argv);
int gettime(t_sim *sim);

int check_arg(int argc, char **argv);

void start(t_philo *philo);
void end(t_philo *philo);
void watch(t_sim *sim, t_philo *philo);
int check_meals(t_sim *sim, t_philo *philo);
void ft_sleep(int time);
int getrealtime();

#endif