/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:21:04 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 13:21:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	free_all(t_philo *philos)
//{
//	int i;
//	i = -1;

//	free(philos);
//}

int gettime(t_philo *philo)
{
	static unsigned long start;
	struct timeval tv;
	(void)philo;
	gettimeofday(&tv, NULL);
	if (!start)
		start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start);
}
