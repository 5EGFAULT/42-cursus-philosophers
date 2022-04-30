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
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
typedef enum e_state
{
	NONE,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}t_state;
typedef struct s_philo
{
	int			id;
	int			fork_left;
	int			fork_right;
	int			last_meal;
	int			nb_times_eat;
	t_state		state;
	pthread_t	*thread;
}t_philo;
typedef struct s_simululation
{
	int 			nb_philos;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			time_to_die;
	int 			nb_times_to_eat;
	int 			dead_philo;
	int 			*forks;
	pthread_mutex_t fork_lock;
	struct timeval	tv;
	struct timezone	tz;
	t_philo 		*philos;
}t_simululation;

typedef struct s_arg
{
	t_philo *philo;
	t_simululation *sim;
}t_arg;

int	ft_atoi(const char *str);
t_philo			*init_philo(int nbr_philo, t_simululation *sim);
t_simululation	*init_sim(int argc, char **argv);
void			free_sim(t_simululation *sim);
void			init_mutex(t_simululation *sim);
void			start_sim(t_simululation *sim);
void			*run_philo(void *arg);

void			philo_eat(t_philo *philo, t_simululation *sim, int *b);
void			philo_think(t_philo *philo, t_simululation *sim, int *b);
void			philo_sleep(t_philo *philo, t_simululation *sim, int *b);

#endif