/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:20:31 by asouinia          #+#    #+#             */
/*   Updated: 2022/06/15 22:31:12 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_fork(t_philo *philo)
{
	sem_wait(philo->sim->forks);
	print_line(philo, "has taken a fork");
	sem_wait(philo->sim->forks);
	print_line(philo, "has taken a fork");
	return (0);
}

int	leave_fork(t_philo *philo)
{
	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);
	return (0);
}

int	eat(t_philo *philo)
{
	take_fork(philo);
	print_line(philo, "is eating");
	++(philo->nb_times_eat);
	philo->last_meal = getime();
	ft_sleep(philo->sim->time_to_eat, philo->sim->nb_philo);
	leave_fork(philo);
	return (0);
}
