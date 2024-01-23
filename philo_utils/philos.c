/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:23:00 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/23 05:17:16 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	odd_routine(t_philo *philos)
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
	if ((philos->rules->eat_limit) >= 0 && ((philos->meal_count)
			>= (philos->rules->eat_limit)))
	{
		pthread_mutex_lock(&(philos->rules->full_mtx));
		(philos->rules->full) += 1;
		pthread_mutex_unlock(&(philos->rules->full_mtx));
		return (false);
	}
	safe_print_t_d('t', philos, get_time(&(philos->rules->timer)));
	return (true);
}

static bool	even_routine(t_philo *philos)
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
	if ((philos->rules->eat_limit) >= 0 && ((philos->meal_count)
			>= (philos->rules->eat_limit)))
	{
		pthread_mutex_lock(&(philos->rules->full_mtx));
		(philos->rules->full) += 1;
		pthread_mutex_unlock(&(philos->rules->full_mtx));
		return (false);
	}
	safe_print_t_d('t', philos, get_time(&(philos->rules->timer)));
	return (true);
}

void	*philo_routine(void *ph)
{
	t_philo	*philos;

	philos = (t_philo *)ph;
	while (1)
	{
		if ((philos->id) % 2 == 0)
		{
			if (!even_routine(philos))
				break ;
		}
		else
		{
			if (!odd_routine(philos))
				break ;
		}
	}
	return (NULL);
}

bool	start_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = rules->philos;
	gettimeofday(&(rules->timer.start_time), NULL);
	while (i < rules->phs_nb)
	{
		pthread_create(&(philos[i].th), NULL, philo_routine, &(philos[i]));
		i++;
	}
	pthread_create(&(rules->sudo.th), NULL, sudo_routine, &(rules->sudo));
	return (true);
}

void	wait_for_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = rules->philos;
	while (i < rules->phs_nb)
	{
		pthread_detach((philos[i].th));
		i++;
	}
	pthread_detach((rules->sudo.th));
}
