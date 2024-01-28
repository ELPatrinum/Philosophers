#include "philo.h"

void	ft_usleep(unsigned int usec)
{
	struct timeval	now;
	size_t			start;
	size_t			current;

	gettimeofday(&now, NULL);
	current = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	start = current;
	while (current - start < (usec / 1000))
	{
		gettimeofday(&now, NULL);
		current = (now.tv_sec * 1000) + (now.tv_usec / 1000);
		usleep(50);
	}
}

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	safe_print_f_e_s(char c, t_philo *philos, unsigned int ts)
{
	if (c == 'f')
	{
		sem_wait(philos->data->write);
		printf("%u %d has taken a fork\n", ts, philos->index + 1);
		sem_post(philos->data->write);
	}
	else if (c == 'e')
	{
		sem_wait(philos->data->write);
		printf("%u %d is eating\n", ts, philos->index + 1);
		sem_post(philos->data->write);
	}
	else if (c == 's')
	{
		sem_wait(philos->data->write);
		printf("%u %d is sleeping\n", ts, philos->index + 1);
		sem_post(philos->data->write);
	}
}

void	safe_print_t_d(char c, t_philo *philos, unsigned int ts)
{
	if (c == 't')
	{
		sem_wait(philos->data->write);
		printf("%u %d is thinking\n", ts, philos->index + 1);
		sem_post(philos->data->write);
	}
	else if (c == 'd')
	{
		sem_wait(philos->data->write);;
		printf("%u %d died\n", ts, philos->index + 1);
	}
}
