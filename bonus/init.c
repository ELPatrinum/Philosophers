/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:29 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/28 17:53:04 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	sem_unlink("write");
	rules->write_sem = sem_open("write", O_CREAT, 0600, 1);
	
	while (++i < (rules->phs_nb))
	{
		sem_unlink("fork");
		rules->forks[i].fork = sem_open("fork", O_CREAT, 0600, 1);
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
		assign_forks(&(rules->philos[i]), rules->forks, i, rules->phs_nb);
	}
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
