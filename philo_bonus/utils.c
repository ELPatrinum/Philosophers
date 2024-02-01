/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:49 by muel-bak          #+#    #+#             */
/*   Updated: 2024/02/01 10:42:20 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned int usec, t_philo *philos, int check)
{
	struct timeval	now;
	size_t			start;
	size_t			current;

	gettimeofday(&now, NULL);
	current = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	start = current;
	while (current - start < (usec / 1000))
	{
		if ((check == 1) && (((get_time(&(philos->rules->timer)) * 1000)
					- ((philos->last_meal) * 1000) + philos->rules->to_eat)
				> philos->rules->to_die))
		{
			ft_usleep(philos->rules->to_die - ((get_time(&(philos->rules->timer)
							) * 1000) - ((philos->last_meal) * 1000)
					), philos, 0);
			safe_print_t_d('d', philos,
				get_time(&(philos->rules->timer)));
			exit (200);
		}
		gettimeofday(&now, NULL);
		current = (now.tv_sec * 1000) + (now.tv_usec / 1000);
		usleep(50);
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

void	safe_print_f_e_s(char c, t_philo *philos, unsigned int ts)
{
	if (c == 'f')
	{
		sem_wait((philos->rules->write_sem));
		printf("%u %d has taken a fork\n", ts, philos->id);
		sem_post(philos->rules->write_sem);
	}
	else if (c == 'e')
	{
		sem_wait(philos->rules->write_sem);
		printf("%u %d is eating\n", ts, philos->id);
		sem_post(philos->rules->write_sem);
	}
	else if (c == 's')
	{
		sem_wait(philos->rules->write_sem);
		printf("%u %d is sleeping\n", ts, philos->id);
		sem_post(philos->rules->write_sem);
	}
}

void	safe_print_t_d(char c, t_philo *philos, unsigned int ts)
{
	if (c == 't')
	{
		sem_wait(philos->rules->write_sem);
		printf("%u %d is thinking\n", ts, philos->id);
		sem_post(philos->rules->write_sem);
	}
	else if (c == 'd')
	{
		sem_wait(philos->rules->write_sem);
		printf("%u %d died\n", ts, philos->id);
	}
}
