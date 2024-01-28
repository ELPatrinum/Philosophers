/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:07:29 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/28 17:55:13 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_rules	rules;
	int result;

	if ((ac == 5 || ac == 6) && is_valid(av, ac) && ft_atoi(av[1]) <= PH_MAX)
	{
		if (!init_rules(&rules, av, ac))
			return (1);
		start_philos(&rules);

		i = -1;
		while (++i < rules.phs_nb)
		{
			waitpid( -1, &result, 0);
			if (WIFEXITED(result) && WEXITSTATUS(result) == 200)
            	break;
		}
		
		i = -1;
		while (++i < rules.phs_nb)
		{
			kill((rules.philos[i].pid), SIGKILL);
			sem_close(rules.forks[i].fork);
		}
		return (free(rules.philos), free(rules.forks), 0);
	}
	else
		return (error_(av[1]), 1);
}
