/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:21:06 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 11:21:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdatomic.h>

typedef struct s_sim
{
	int		nb_philo;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_to_die;
	int		time_start;
	int		nbr_times_eat;
	sem_t	*forks;
	sem_t	*dead;
}t_sim;

typedef struct s_philo
{
	pid_t		p_id;
	t_sim		*sim;
	pthread_t	thread;
	int			id;
	atomic_int	last_meal;
	atomic_int	nb_times_eat;
}t_philo;

void	ft_sleep(int time, int nbr_philo);
int		getime(void);
int		ft_atoi(const char *str);
int		print_line(t_philo *philo, char *str);
t_sim	*init_sim(int argc, char **argv);
t_philo	*init_philo(int nb_philo, t_sim *sim);
void	*run(void *philo);
void	start(t_philo *philo);
void	end(t_philo *philo);
int		ft_atoi_error(const char *str);
int		check_arg(int argc, char **argv);
int		take_fork(t_philo *philo);
int		leave_fork(t_philo *philo);
int		eat(t_philo *philo);
void	destroy_mutexs(t_philo *philo);
int		watch(t_philo *philo);

#endif