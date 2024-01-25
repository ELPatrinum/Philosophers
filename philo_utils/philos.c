/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:23:00 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/25 09:59:26 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	check_(t_philo *philos)
{
	if ((philos->rules->eat_limit) >= 0 && ((philos->meal_count)
			>= (philos->rules->eat_limit)))
	{
		pthread_mutex_lock(&(philos->rules->full_mtx));
		(philos->rules->full) += 1;
		pthread_mutex_unlock(&(philos->rules->full_mtx));
		return (false);
	}
	pthread_mutex_lock(&(philos->rules->alive_mutex));
	if (!(philos->rules->all_alive))
	{
		pthread_mutex_unlock(&(philos->rules->alive_mutex));
		return (false);
	}
	pthread_mutex_unlock(&(philos->rules->alive_mutex));
	return (true);
}

static bool	routine(t_philo *philos)
{
	pthread_mutex_lock(&(philos->r_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	pthread_mutex_lock(&(philos->l_fork->fork));
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	(philos->meal_count) += 1;
	safe_print_f_e_s('e', philos, get_time(&(philos->rules->timer)));
	pthread_mutex_lock(&(philos->lst_ml_mtx));
	(philos->last_meal) = get_time(&(philos->rules->timer));
	pthread_mutex_unlock(&(philos->lst_ml_mtx));
	ft_usleep((unsigned int)(philos->rules->to_eat));
	pthread_mutex_unlock(&(philos->r_fork->fork));
	pthread_mutex_unlock(&(philos->l_fork->fork));
	safe_print_f_e_s('s', philos, get_time(&(philos->rules->timer)));
	ft_usleep(philos->rules->to_sleep);
	safe_print_t_d('t', philos, get_time(&(philos->rules->timer)));
	if (!check_(philos))
		return (false);
	return (true);
}

void	*philo_routine(void *ph)
{
	t_philo	*philos;

	philos = (t_philo *)ph;
	if ((philos->id) % 2 == 0)
	{
		ft_usleep(100 * 1000);
	}
	while (1)
	{
		if (!routine(philos))
			break ;
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
	pthread_join((rules->sudo.th), NULL);
}
