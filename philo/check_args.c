/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:38:00 by marvin            #+#    #+#             */
/*   Updated: 2022/05/01 16:38:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	check_ft_atoi_inter(int *sign, long nbr, char c)
{
	nbr = nbr * 10 + c - '0';
	if (nbr > 2147483648)
		*sign = -1;
	if (nbr == 2147483648 && *sign > 0)
		*sign = -1;
	return (nbr);
}

int	ft_atoi_error(const char *str)
{
	int		i;
	long	nbr;
	int		sign;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] == ' '))
		++i;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[++i] < '0' || str[i] > '9')
			return (-1);
	}
	else if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		nbr = check_ft_atoi_inter(&sign, nbr, str[i++]);
	if ((str[i] == ' ') || (str[i] == '\0'))
		return (sign * nbr);
	return (-1);
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_atoi_error(argv[i]) <= 0)
			return (0);
	}
	return (1);
}