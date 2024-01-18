/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:02 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/18 20:32:51 by muel-bak         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_rules rules;

	if ((ac == 5 || ac == 6) && is_valid(av, ac) && ft_atoi(av[1]) <= PH_MAX)
	{
		init_rules(&rules, av, ac);
		print_it(&rules);
	}
	else
		return (error_(av[1]));
	return (0);
}
