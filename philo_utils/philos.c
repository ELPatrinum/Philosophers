/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:23:00 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/22 02:44:21 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// bool	sudo_rotine(t_philo *philos, long *count)
// {
// 	if (((get_time(&(philos->rules->timer))) - (philos->last_meal)) <= (philos->rules->to_die))
// 	{
// 		philos->rules->all_alive = false;
// 		return (false);
// 	}
// }

static bool	odd_routine(t_philo *philos, long *count)
{
	pthread_mutex_lock(&(philos->r_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	
	pthread_mutex_lock(&(philos->l_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	safe_print_f_e_s('e', philos, get_time(&(philos->rules->timer)));
	
	ft_usleep(philos->rules->to_eat);
	
	(philos->meal_count) += 1;
	(philos->last_meal) = get_time(&(philos->rules->timer));
	
	pthread_mutex_unlock(&(philos->r_fork->fork));
	pthread_mutex_unlock(&(philos->l_fork->fork));
	
	safe_print_f_e_s('s', philos, get_time(&(philos->rules->timer)));
	ft_usleep(philos->rules->to_sleep);
	if ((philos->rules->eat_limit) >= 0 && ((philos->meal_count) == (philos->rules->eat_limit)))
		return (false);
	return (true);
}

static bool	even_routine(t_philo *philos, long *count)
{
	// if (philos->start)
	// {
	// 	philos->start = false;
	// 	ft_usleep(2000);
	// }
	pthread_mutex_lock(&(philos->l_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	
	pthread_mutex_lock(&(philos->r_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	safe_print_f_e_s('e', philos, get_time(&(philos->rules->timer)));
	
	ft_usleep(philos->rules->to_eat);
	
	(philos->meal_count) += 1;
	(philos->last_meal) = get_time(&(philos->rules->timer));
	
	pthread_mutex_unlock(&(philos->l_fork->fork));
	pthread_mutex_unlock(&(philos->r_fork->fork));
	
	safe_print_f_e_s('s', philos, get_time(&(philos->rules->timer)));
	ft_usleep(philos->rules->to_sleep);
	if ((philos->rules->eat_limit) >= 0 && ((philos->meal_count) == (philos->rules->eat_limit)))
		return (false);
	return (true);
}

void	*rise(t_philo *philos)
{
	long count;
	while(1)
	{
		if ((philos->id) % 2 == 0)
		{
			if (!even_routine(philos, &count))
				break;
		}
		else
		{
			if (!odd_routine(philos, &count))
				break;
		}
	}
	return(NULL);
}


void	start_philos(t_rules *rules)
{
	int i;
	i = 0;
	t_philo	*philos = rules->philos;
	while (i < rules->phs_nb)
	{
		pthread_create(&(philos[i].th), NULL, (void * _Nullable)rise, &(philos[i]));
		i++;
	}
	
}
void	wait_for_philosvoid(t_rules *rules)
{
	int i;
	i = 0;
	t_philo	*philos = rules->philos;
	while (i < rules->phs_nb)
	{
		pthread_join((philos[i].th), NULL);
		i++;
	}
}
