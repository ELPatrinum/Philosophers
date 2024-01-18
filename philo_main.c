/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:02 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/18 23:08:58 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_it(t_rules *rules)
{
	printf("===========================================\n");
	printf("rules->phs_nb     :%zu:\n", rules->phs_nb);
	printf("rules->to_die     :%zu:\n", rules->to_die);
	printf("rules->to_eat     :%zu:\n", rules->to_eat);
	printf("rules->to_sleep   :%zu:\n", rules->to_sleep);
	printf("rules->eat_limit  :%ld:\n", rules->eat_limit);
	printf("===========================================\n");
}

void	print_philo(t_philo *philos, int nbr)
{
	int i = -1;
	while (++i < nbr)
	{
		printf("===========================================\n");
		printf("philo_id :%d:\n", philos[i].id);
		printf("r_fork_id :%d:\n", philos[i].r_fork->fork_id);
		printf("l_fork_id :%d:\n", philos[i].l_fork->fork_id);
		printf("===========================================\n");
	}
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if ((ac == 5 || ac == 6) && is_valid(av, ac) && ft_atoi(av[1]) <= PH_MAX)
	{
		init_rules(&rules, av, ac);
		print_philo(rules.philos, rules.phs_nb);
		// print_it(&rules);
	}
	else
		return (error_(av[1]));
	return (0);
}
