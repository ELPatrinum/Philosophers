/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:29 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/28 16:19:02 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_(char **av, int ac, t_rules *rules)
{
	if (ac == 5)
	{
		rules->eat_max = -1;
		rules->eat_counter = -1;
		rules->max_eat = -1;
	}
	else
	{
		rules->philo_numbers = ft_atoi(av[1]);
		rules->eat_max = ft_atoi(av[5]);
		rules->eat_counter = 0;
		rules->max_eat = rules->eat_max * rules->philo_numbers;
	}
	rules->philo_numbers = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	return (0);
}

void	create_semaphores(t_rules *rules)
{
	sem_unlink("death");
	rules->death = sem_open("death", O_CREAT, 0600, 1);
	sem_unlink("write");
	rules->write = sem_open("write", O_CREAT, 0600, 1);
	sem_unlink("stop");
	rules->stop = sem_open("stop", O_CREAT, 0600, 1);
	sem_unlink("forks");
	rules->forks = sem_open("forks", O_CREAT, 0600,
			rules->philo_numbers);
}

t_philo	*ft_philo_init(t_rules *rules)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * rules->philo_numbers);
	if (!philo)
		return (NULL);
	rules->death = NULL;
	rules->stop = NULL;
	rules->write = NULL;
	rules->forks = NULL;
	while (++i < rules->philo_numbers)
	{
		philo[i].index = i;
		philo[i].is_dead = NO;
		philo[i].data = rules;
		philo[i].pid = -1;
		philo[i].meal_count = 0;
		if (rules->eat_max == -1)
			philo[i].eat_max = -1;
		else
			philo[i].eat_max = rules->eat_max;
	}
	return (philo);
}
