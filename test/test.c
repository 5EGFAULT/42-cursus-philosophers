#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int getime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_sleep(int time)
{
	size_t i;

	i = getime();
	// usleep(time * 800);
	while (getime() - i < (size_t)time)
		usleep(100);
}

int main(int ac, char **av)
{
	int i;
	pthread_mutex_t mutex;

	i = getime();
	pthread_mutex_init(&mutex, NULL);
	printf("%d \n", getime() - i);
	printf("%d  l %d\n", getime() - i, pthread_mutex_lock(&mutex));
	pthread_mutex_destroy(&mutex);
	printf("%d  unl %d\n", getime() - i, pthread_mutex_unlock(&mutex));
	return (0);
}
