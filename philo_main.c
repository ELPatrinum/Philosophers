/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:02 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/23 01:34:02 by muel-bak         ###   ########.fr       */
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

// void	f()
// {
// 	system("leaks philo");
// }

int main(int ac, char **av)
{
	// atexit(f);
    t_rules rules;
    if ((ac == 5 || ac == 6) && is_valid(av, ac) && ft_atoi(av[1]) <= PH_MAX)
	{
        init_rules(&rules, av, ac);
        if (start_philos(&rules))
		{
			while (rules.all_alive);
		}
    	 wait_for_philos(&rules);
    }
	else
	{
        return error_(av[0]);
    }
    pthread_mutex_destroy(&(rules.write_mutex));
    pthread_mutex_destroy(&(rules.full_mtx));
	pthread_mutex_destroy(&(rules.philos->lst_ml_mtx));
	pthread_mutex_destroy(&(rules.full_mtx));
	int i = -1;
	while (++i < (rules.phs_nb))
	{
		pthread_mutex_destroy(&(rules.forks[i].fork));
	}
    free(rules.forks);
    free(rules.philos);
    return 0;
}
