/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:02 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/17 15:37:52 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_it(t_philo *philo, bool *i)
{
	if (*i)
	{
		printf("===========================================\n");
		*i = false;
	}
	printf("philo->id         :%d:\n", philo->id);
	printf("philo->phs_nb     :%zu:\n", philo->phs_nb);
	printf("philo->to_die     :%zu:\n", philo->to_die);
	printf("philo->to_eat     :%zu:\n", philo->to_eat);
	printf("philo->to_sleep   :%zu:\n", philo->to_sleep);
	printf("philo->eat_limit  :%zu:\n", philo->eat_limit);
	printf("===========================================\n");
}

void	print_struct(t_philo *philo, char **av)
{
	bool ck = true;
	int i = 0;
	while (i < ft_atoi(av[1]))
	{
		print_it(&philo[i], &ck);
		i++;
	}

}

int	main(int ac, char **av)
{
	bool	check;
	t_philo	philo[PH_MAX];

	if ((ac == 5 || ac == 6) && is_valid(av, ac) && ft_atoi(av[1]) <= PH_MAX)
	{
		if (ac == 6)
			check = true;
		init_philo(philo, check, av);
		print_struct(philo, av);
	}
	else
		return (print_error());
	return (0);
}
