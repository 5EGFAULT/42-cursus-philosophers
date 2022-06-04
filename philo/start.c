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

void	start_sim(t_simululation *sim)
{
	int				i;
	t_arg			*arg;

	i = -1;
	while (++i < sim->nb_philos)
	{
		arg = (t_arg *)malloc(sizeof(t_arg));
		if (!arg)
			return ;
		arg->philo = &(sim->philos[i]);
		arg->sim = sim;
		pthread_create(sim->philos[i].thread, NULL, &run_philo, (void *)arg);
	}
	i = -1;
	while (++i < sim->nb_philos)
		pthread_join(*(sim->philos[i].thread), NULL);
}
