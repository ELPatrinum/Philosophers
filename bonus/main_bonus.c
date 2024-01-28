/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:07:29 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/28 10:54:21 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				i;
	t_rules	rules;
	t_philo			*philo;

	if ((ac == 5 || ac == 6) && is_valid(av, ac) && ft_atoi(av[1]) <= PH_MAX)
	{
		init_(av, ac, &rules);
		philo = ft_philo_init(&rules);
		if (!philo)
			return (2);
		create_semaphores(&rules);
		sem_wait(rules.stop);
		start_process(&rules, philo);
		sem_wait(rules.stop);
		i = 0;
		while (i < rules.philo_numbers)
			kill(philo[i++].pid, SIGKILL);
		sem_close(rules.death);
		sem_close(rules.write);
		sem_close(rules.stop);
		sem_close(rules.forks);
		free(philo);
	}
	else
		return (error_(av[1]), 1);
	return (0);
}
