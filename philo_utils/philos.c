/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:23:00 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/22 20:24:58 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


static bool	odd_routine(t_philo *philos, long *count)
{
	pthread_mutex_lock(&(philos->r_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	
	pthread_mutex_lock(&(philos->l_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	safe_print_f_e_s('e', philos, get_time(&(philos->rules->timer)));
	
	ft_usleep(philos->rules->to_eat);
	
	(philos->meal_count) += 1;
	
	pthread_mutex_lock(&(philos->lst_ml_mtx));
	(philos->last_meal) = get_time(&(philos->rules->timer));
	pthread_mutex_unlock(&(philos->lst_ml_mtx));
	
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
	pthread_mutex_lock(&(philos->l_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	
	pthread_mutex_lock(&(philos->r_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	safe_print_f_e_s('e', philos, get_time(&(philos->rules->timer)));
	
	ft_usleep(philos->rules->to_eat);
	
	(philos->meal_count) += 1;
	
	pthread_mutex_lock(&(philos->lst_ml_mtx));
	(philos->last_meal) = get_time(&(philos->rules->timer));
	pthread_mutex_unlock(&(philos->lst_ml_mtx));
	
	pthread_mutex_unlock(&(philos->l_fork->fork));
	pthread_mutex_unlock(&(philos->r_fork->fork));
	
	safe_print_f_e_s('s', philos, get_time(&(philos->rules->timer)));
	ft_usleep(philos->rules->to_sleep);
	if ((philos->rules->eat_limit) >= 0 && ((philos->meal_count) == (philos->rules->eat_limit)))
		return (false);
	return (true);
}

void	*philo_routine(t_philo *philos)
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

void	*sudo_routine(t_sudo *sudo)
{
	int i;

	i = 0;
	while (i >= 0)
	{
		i = 0;
		while (i < sudo->philos->rules->phs_nb)
		{
			pthread_mutex_lock(&(sudo->philos[i].lst_ml_mtx));
			if ((get_time(&(sudo->philos->rules->timer)) * 1000) - ((sudo->philos[i].last_meal) * 1000) > (sudo->philos->rules->to_die))
				{
					sudo->philos->rules->all_alive = false;
					safe_print_t_d('d', &(sudo->philos[i]), get_time(&(sudo->philos->rules->timer)));
					pthread_mutex_unlock(&(sudo->philos[i].lst_ml_mtx));
					i = -1;
					exit(EXIT_FAILURE);
					break;
				}
			pthread_mutex_unlock(&(sudo->philos[i].lst_ml_mtx));
			i++;
		}
	}
	return (NULL);
}


void	start_philos(t_rules *rules)
{
	int i;
	i = 0;
	t_philo	*philos = rules->philos;
	while (i < rules->phs_nb)
	{
		pthread_create(&(philos[i].th), NULL, (void * _Nullable)philo_routine, &(philos[i]));
		i++;
	}
	pthread_create(&(rules->sudo.th), NULL, (void * _Nullable)sudo_routine, &(rules->sudo));
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
	pthread_join((rules->sudo.th), NULL);
}
