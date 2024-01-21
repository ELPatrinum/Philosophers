/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:23:00 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/21 17:42:41 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*rise(t_rules *rules)
{
	pthread_mutex_lock(&(rules->write_mutex));
	printf("philo number :%d: is up\n", rules->philos->id);
	pthread_mutex_unlock(&(rules->write_mutex));
	while(1);
}


void start_philos(t_rules *rules)
{
	int i;
	t_philo	*philos = rules->philos;
	i = -1;
	while (++i < rules->phs_nb)
	{
		pthread_create(&(philos[i].th), NULL, (void * _Nullable)&rise, rules);
	}
}
