/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:02 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/25 09:37:48 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_max(t_rules *rules)
{
	size_t	max;
	int		i;

	i = 0;
	max = rules->to_die;
	if (rules->to_eat > max)
		max = rules->to_eat;
	if (rules->to_sleep > max)
		max = rules->to_sleep;
	return (max);
}

int	main(int ac, char **av)
{
	t_rules	rules;
	int		i;

	if ((ac == 5 || ac == 6) && is_valid(av, ac) && ft_atoi(av[1]) <= PH_MAX)
	{
		if (!init_rules(&rules, av, ac))
			return (1);
		if (start_philos(&rules))
			while (rules.all_alive)
				i = -1;
		wait_for_philos(&rules);
	}
	else
		return (error_(av[1]), 1);
	ft_usleep(get_max(&rules));
	pthread_mutex_destroy(&(rules.write_mutex));
	pthread_mutex_destroy(&(rules.full_mtx));
	pthread_mutex_destroy(&(rules.philos->lst_ml_mtx));
	pthread_mutex_destroy(&(rules.full_mtx));
	i = -1;
	while (++i < (rules.phs_nb))
	{
		pthread_mutex_destroy(&(rules.forks[i].fork));
	}
	return (free(rules.forks), free(rules.philos), 0);
}
