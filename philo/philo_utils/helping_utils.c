/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:28:54 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/25 04:33:01 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	safe_print_f_e_s(char c, t_philo *philos, unsigned int ts)
{
	if (c == 'f')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d has taken a fork\n", ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));
	}
	else if (c == 'e')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d is eating\n", ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));
	}
	else if (c == 's')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d is sleeping\n", ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));
	}
}

void	safe_print_t_d(char c, t_philo *philos, unsigned int ts)
{
	if (c == 't')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d is thinking\n", ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));
	}
	else if (c == 'd')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d died\n", ts, philos->id);
	}
}

size_t	get_time(t_timer *timer)
{
	struct timeval	current_time;
	size_t			elapsed_time_ms;
	size_t			tmp_time_ms;

	gettimeofday(&current_time, NULL);
	elapsed_time_ms = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	tmp_time_ms = (timer->start_time.tv_sec * 1000)
		+ (timer->start_time.tv_usec / 1000);
	return (elapsed_time_ms - tmp_time_ms);
}
