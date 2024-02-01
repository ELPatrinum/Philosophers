/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:47:41 by muel-bak          #+#    #+#             */
/*   Updated: 2024/02/01 12:29:03 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	is_dead(t_sudo *sudo, int *i)
{
	pthread_mutex_lock(&(sudo->philos[*i].lst_ml_mtx));
	pthread_mutex_lock(&(sudo->philos[*i].ml_ct_mtx));
	if ((get_time(&(sudo->philos->rules->timer)) * 1000)
		- ((sudo->philos[*i].last_meal) * 1000) > (sudo->philos->rules->to_die)
		&& ((sudo->philos[*i].meal_count) != -3))
	{
		pthread_mutex_lock(&(sudo->philos->rules->alive_mutex));
		(sudo->philos->rules->all_alive) = false;
		pthread_mutex_unlock(&(sudo->philos->rules->alive_mutex));
		safe_print_t_d('d', &(sudo->philos[*i]),
			get_time(&(sudo->philos->rules->timer)));
		pthread_mutex_unlock(&(sudo->philos[*i].ml_ct_mtx));
		pthread_mutex_unlock(&(sudo->philos[*i].lst_ml_mtx));
		(*i) = -10;
		return (true);
	}
	pthread_mutex_unlock(&(sudo->philos[*i].ml_ct_mtx));
	pthread_mutex_unlock(&(sudo->philos[*i].lst_ml_mtx));
	return (false);
}

static bool	is_full(t_sudo *sudo, int *i)
{
	if (sudo->philos->rules->full == sudo->philos->rules->phs_nb
		&& *i == sudo->philos->rules->phs_nb - 1)
	{
		pthread_mutex_lock(&(sudo->philos->rules->write_mutex));
		pthread_mutex_unlock(&(sudo->philos->rules->full_mtx));
		(sudo->philos->rules->all_alive) = false;
		(*i) = -10;
		return (true);
	}
	return (false);
}

void	*sudo_routine(void *sdo)
{
	t_sudo	*sudo;
	int		i;

	i = 1;
	sudo = (t_sudo *)sdo;
	while (i > 0)
	{
		i = 0;
		while (i < (sudo->philos->rules->phs_nb))
		{
			if (is_dead(sudo, &i))
				return (NULL);
			pthread_mutex_lock(&(sudo->philos->rules->full_mtx));
			if (is_full(sudo, &i))
				return (NULL);
			pthread_mutex_unlock(&(sudo->philos->rules->full_mtx));
			i++;
		}
	}
	return (NULL);
}
