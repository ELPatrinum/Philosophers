/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:28:54 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/23 00:26:10 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_usleep(unsigned int usec)
{
    struct timeval start;
    struct timeval now;
    struct timeval end;
    gettimeofday(&start, NULL);
    end.tv_sec = start.tv_sec + (usec / 1000000);
    end.tv_usec = start.tv_usec + (usec % 1000000);
    if (end.tv_usec >= 1000000)
    {
        end.tv_sec++;
        end.tv_usec -= 1000000;
    }
    while (1)
    {
        gettimeofday(&now, NULL);
        if (now.tv_sec > end.tv_sec ||
            (now.tv_sec == end.tv_sec && now.tv_usec >= end.tv_usec))
        {
           break;
        }
    }
}
// {
// 	printf("<<<<%d>>>>\n", usec);
// 	exit(0);
// 	struct timeval t;
// 	gettimeofday(&t, NULL);
// 	while ()
// }
void	safe_print_f_e_s(char c, t_philo *philos, unsigned int ts)
{
	if (c == 'f')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d has taken a fork\n",ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));
	}
	else if (c == 'e')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d is eating\n",ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));		
	}
	else if (c == 's')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d is sleeping\n",ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));		
	}
}

void	safe_print_t_d(char c,  t_philo *philos, unsigned int ts)
{
	if (c == 't')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d is thinking\n",ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));	
	}
	else if (c == 'd')
	{
		pthread_mutex_lock(&(philos->rules->write_mutex));
		printf("%u %d died\n",ts, philos->id);
		pthread_mutex_unlock(&(philos->rules->write_mutex));		
	}
}

size_t get_time(t_timer* timer)
{
    struct timeval current_time;
    size_t elapsed_time_ms;
    gettimeofday(&current_time, NULL);
    elapsed_time_ms = (current_time.tv_sec - timer->start_time.tv_sec) * 1000 +
                           (current_time.tv_usec - timer->start_time.tv_usec) / 1000;
    return (elapsed_time_ms);
}
