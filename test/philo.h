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

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
typedef struct s_sim
{
	int nb_philo;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int time_start;
	int nbr_times_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t dead;
	pthread_mutex_t data;
	int end;

} t_sim;

typedef struct s_philo
{
	pthread_t thread;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	// pthread_mutex_t data;
	int id;
	int last_meal;
	int nb_times_eat;
	int error;
	t_sim *sim;
} t_philo;

//! utils.c
int getime();
void ft_sleep(int time, int nbr_philo);
int ft_atoi(const char *str);
int print_line(t_philo *philo, char *str);

//! init.c
t_sim *init_sim(int argc, char **argv);
t_philo *init_philo(int nb_philo, t_sim *sim);

//! start.c
void *run(void *philo);
void start(t_philo *philo);
void end(t_philo *philo);

//! check_args.c
int ft_atoi_error(const char *str);
int check_arg(int argc, char **argv);

//! eat.c
int take_fork(t_philo *philo);
int leave_fork(t_philo *philo);
int eat(t_philo *philo);

void destroy_mutexs(t_philo *philo);
int watch(t_philo *philo);

#endif