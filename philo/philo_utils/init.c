/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:48:48 by muel-bak          #+#    #+#             */
/*   Updated: 2024/02/01 12:22:43 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int i, int nbr)
{
	if (!philo || !forks)
	{
		printf("assign_forks : NULL ptr\n");
		return ;
	}
	if (i == nbr - 1)
	{
		philo->r_fork = &forks[nbr - 1];
		philo->l_fork = &forks[0];
	}
	else if (i >= 0)
	{
		philo->r_fork = &forks[i];
		philo->l_fork = &forks[i + 1];
	}
}

static bool	init_forks(t_rules *rules)
{
	long	i;

	i = -1;
	if (pthread_mutex_init(&(rules->write_mutex), NULL) == -1)
	{
		return (false);
	}
	if (pthread_mutex_init(&(rules->full_mtx), NULL) == -1)
	{
		return (false);
	}
	while (++i < (rules->phs_nb))
	{
		if (pthread_mutex_init(&(rules->forks[i].fork), NULL) == -1)
		{
			free(rules->forks);
			free(rules->philos);
			return (false);
		}
		rules->forks[i].fork_id = i;
	}
	return (true);
}

static bool	init_philos(t_rules *rules)
{
	long	i;

	i = -1;
	while (++i < (rules->phs_nb))
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meal_count = 0;
		rules->philos[i].start = true;
		rules->philos[i].rules = rules;
		rules->philos[i].last_meal = 0;
		if (pthread_mutex_init(&(rules->philos[i].lst_ml_mtx), NULL) == -1)
			return (false);
		if (pthread_mutex_init(&(rules->philos[i].ml_ct_mtx), NULL) == -1)
			return (false);
		assign_forks(&(rules->philos[i]), rules->forks, i, rules->phs_nb);
	}
	if (pthread_mutex_init(&(rules->alive_mutex), NULL) == -1)
		return (false);
	rules->sudo.sudo_id = -1;
	rules->sudo.philos = (rules->philos);
	return (true);
}

bool	init_rules(t_rules *rules, char **av, int ac)
{
	if (ac == 6)
		rules->eat_limit = (long)ft_atoi(av[5]);
	else
		rules->eat_limit = -1;
	rules->phs_nb = ft_atoi(av[1]);
	rules->time = 0;
	rules->to_die = (ft_atoi(av[2]) * 1000);
	rules->to_eat = (ft_atoi(av[3]) * 1000);
	rules->to_sleep = (ft_atoi(av[4]) * 1000);
	rules->all_alive = true;
	rules->full = 0;
	rules->philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!(rules->philos))
		return (false);
	rules->forks = malloc(sizeof(t_fork) * ft_atoi(av[1]));
	if (!rules->forks)
	{
		free(rules->philos);
		return (false);
	}
	if (!init_forks(rules) ||!init_philos(rules))
		return (false);
	return (true);
}
