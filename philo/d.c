
void	philo_eat(t_philo *philo, t_simululation *sim, int *b)
{
	pthread_mutex_lock(&sim->dead_lock);
	if (sim->dead_philo)
	{
		*b = -1;
		pthread_mutex_unlock(&sim->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&sim->dead_lock);
	gettimeofday(sim->tv, sim->tz);
	if (sim->tv->tv_usec - philo->last_meal > sim->time_to_die)
	{
		*b = philo->id;		
		pthread_mutex_lock(&sim->dead_lock);
		sim->dead_philo = philo->id;
		pthread_mutex_unlock(&sim->dead_lock);
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d is died\n", sim->tv->tv_usec, philo->id);
		memset(sim->forks, 0, sizeof(int) * sim->nb_philos);
		return ;
	}
	if (philo->fork_left && philo->fork_right)
	{
		philo->state = EATING;
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d is eating\n", sim->tv->tv_usec, philo->id);
		usleep(sim->time_to_eat);
		gettimeofday(sim->tv, sim->tz);
		philo->last_meal = sim->tv->tv_usec;
		philo->fork_left = 0;
		philo->fork_right = 0;
		pthread_mutex_lock(&sim->fork_lock);
		if (philo->id == sim->nb_philos || philo->id == 1)
		{
				sim->forks[sim->nb_philos - 1] = 1;
				sim->forks[0] = 1;
		}
		else
		{
			sim->forks[philo->id - 1] = 1;
			sim->forks[philo->id] = 1;
		}
		pthread_mutex_unlock(&sim->fork_lock);
	}
	else  if (!philo->fork_left)
	{
		pthread_mutex_lock(&sim->fork_lock);
		if (philo->id > 1 && sim->forks[philo->id - 1])
		{
			philo->fork_left = 1;
			sim->forks[philo->id - 1] = 0;
		}
		else if (sim->forks[sim->nb_philos - 1])
		{
			philo->fork_left = 1;
			sim->forks[sim->nb_philos - 1] = 0;
		}
		if (philo->fork_left)
		{
			gettimeofday(sim->tv, sim->tz);
				pthread_mutex_lock(&sim->dead_lock);
	if (sim->dead_philo)
	{
		*b = -1;
		pthread_mutex_unlock(&sim->dead_lock);
		return ;
	}
			printf("%ld %d is has taken a fork left\n", sim->tv->tv_usec, philo->id);
	pthread_mutex_unlock(&sim->dead_lock);
		}
		pthread_mutex_unlock(&sim->fork_lock);
	}
	else if (!philo->fork_right)
	{
		pthread_mutex_lock(&sim->fork_lock);
		if (philo->id < sim->nb_philos && sim->forks[philo->id])
		{
			philo->fork_right = 1;
			sim->forks[philo->id - 1] = 0;
		}
		else if (sim->forks[0])
		{
			philo->fork_right = 1;
			sim->forks[0] = 0;
		}
		if (philo->fork_right)
		{
			gettimeofday(sim->tv, sim->tz);
			printf("%ld %d is has taken a fork right\n", sim->tv->tv_usec, philo->id);
		}
		pthread_mutex_unlock(&sim->fork_lock);
	}
}

void	philo_think(t_philo *philo, t_simululation *sim, int *b)
{
	pthread_mutex_lock(&sim->dead_lock);
	if (sim->time_to_die)
	{
		*b = -1;
		pthread_mutex_unlock(&sim->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&sim->dead_lock);
	gettimeofday(sim->tv, sim->tz);
	if (sim->tv->tv_usec - philo->last_meal > sim->time_to_die)
	{
		*b = philo->id;
		pthread_mutex_lock(&sim->dead_lock);
		sim->dead_philo = philo->id;
		pthread_mutex_unlock(&sim->dead_lock);
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d is died\n", sim->tv->tv_usec, philo->id);
		memset(sim->forks, 0, sizeof(int) * sim->nb_philos);
		return ;
	}
	printf("%ld %d is thinking\n", sim->tv->tv_usec, philo->id);
	usleep(sim->time_to_die);
}

void	philo_sleep(t_philo *philo, t_simululation *sim, int *b)
{
	pthread_mutex_lock(&sim->dead_lock);
	if (sim->time_to_die)
	{
		*b = -1;
		pthread_mutex_unlock(&sim->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&sim->dead_lock);
	gettimeofday(sim->tv, sim->tz);
	if (sim->tv->tv_usec - philo->last_meal > sim->time_to_die)
	{
		*b = philo->id;
		pthread_mutex_lock(&sim->dead_lock);
		sim->dead_philo = philo->id;
		pthread_mutex_unlock(&sim->dead_lock);
		gettimeofday(sim->tv, sim->tz);
		printf("%ld %d is died\n", sim->tv->tv_usec, philo->id);
		memset(sim->forks, 0, sizeof(int) * sim->nb_philos);
		return ;
	}
	printf("%ld %d is sleeping\n", sim->tv->tv_usec, philo->id);
	usleep(sim->time_to_sleep);
}

