/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:48:48 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/21 17:16:55 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int i, int nbr)
{
	if (!philo || !forks)
	{
		printf("assign_forks : NULL ptr\n");
		exit(EXIT_FAILURE);
	}
	if (i == nbr - 1)
	{
		philo->r_fork = &forks[nbr - 1];
		philo->l_fork = &forks[0];
	}
	else if (i >= 0)
	{
		philo->r_fork = &forks[i];
		printf("philo_id:%d: r_fork_id:%d:\n",philo->id, philo->r_fork->fork_id);
		philo->l_fork = &forks[i + 1];
		printf("philo_id:%d: l_fork_id :%d:\n",philo->id, philo->l_fork->fork_id);
	}
}

static void	init_forks(t_rules *rules)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(rules->write_mutex), NULL) == -1)
	{
		exit(EXIT_FAILURE);
	}
	while (++i < rules->phs_nb)
	{
		if (pthread_mutex_init(&(rules->forks[i].fork), NULL) == -1)
		{
			free(rules->forks);
			free(rules->philos);
			exit(EXIT_FAILURE);
		}
		rules->forks[i].fork_id = i;
	}
}

static void	init_philos(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->phs_nb)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meal_count = 0;
		rules->philos[i].full = false;
		rules->philos[i].rules = rules;
		assign_forks(&(rules->philos[i]), rules->forks, i, rules->phs_nb);
	}
}

void	init_rules(t_rules *rules, char **av, int ac)
{
	size_t	n;

	n = ft_atoi(av[1]);
	if (ac == 6)
		rules->eat_limit = (long)ft_atoi(av[5]);
	else
		rules->eat_limit = -1;
	rules->phs_nb = n;
	rules->to_die = ft_atoi(av[2]);
	rules->to_eat = ft_atoi(av[3]);
	rules->to_sleep = ft_atoi(av[4]);
	rules->philos = malloc(sizeof(t_philo) * n);
	if (!rules->philos)
		exit(EXIT_FAILURE);
	rules->forks = malloc(sizeof(t_fork) * n);
	if (!rules->forks)
	{
		free(rules->philos);
		exit(EXIT_FAILURE);
	}
	init_forks(rules);
	init_philos(rules);
}
