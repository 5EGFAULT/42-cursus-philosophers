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
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			id;
	int			fork_left;
	int			fork_right;
	long int	last_meal;
	int			nb_times_eat;
	pthread_t	*thread;
	t_sim		*sim;
}t_philo;
typedef struct s_sim
{
	int 			nb_philos;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			time_to_die;
	int 			nb_times_to_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	long int		start_time;
	struct timeval	*tv;
	struct timezone	*tz;
}t_sim;

int	ft_atoi(const char *str);
t_philo			*init_philo(int nbr_philo, t_sim *sim);
t_sim	*init_sim(int argc, char **argv);
void			free_sim(t_sim *sim);
void			init_mutex(t_sim *sim);
void			start_sim(t_sim *sim);
int				check_arg(int argc, char **argv);

#endif