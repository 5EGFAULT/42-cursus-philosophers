/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:24:13 by marvin            #+#    #+#             */
/*   Updated: 2022/04/30 11:24:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_simululation	*sim;

	if (argc < 5 || argc > 6)
		return (printf("philo params error.\nUsage: ./philo \
<number of philosophers> <time to eat> <time to sleep> <time to die> \
[number of times each philosopher must eat]\n"), 2);
	if (!check_arg(argc, argv))
		return (printf("philo params error.\nUsage: params must be \
integers bigger than 0\n"), 2);
	sim = init_sim(argc, argv);
	if (!sim)
		return (printf("philo malloc error.\n"), 3);
	start_sim(sim);
	free_sim(sim);
	return (0);
}

