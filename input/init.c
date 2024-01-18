/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:48:48 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/17 16:25:07 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void init_philo_input(t_philo *philo, char **av, bool check, int i)
{
	if (check)
		philo->eat_limit = ft_atoi(av[5]);
	else
		philo->eat_limit = -1;
	philo->phs_nb = ft_atoi(av[1]);
	philo->to_die = ft_atoi(av[2]);
	philo->to_eat = ft_atoi(av[3]);
	philo->to_sleep = ft_atoi(av[4]);
	philo->id = i;
}

void	init_philo(t_philo *philo, bool check, char **av)
{
	size_t	i;

	i = 1;
	while (i <= ft_atoi(av[1]))
	{
		init_philo_input(&philo[i - 1], av, check, i);
		i++;
	}
}
void	*fct(void)
{
	
}

bool	start_threads(t_philo *philo, int nbr)
{
	int	i;
	pthread_t	th[nbr];
	i = 0;
	while (i < nbr)
	{
		if (pthread_create(&th[i++], NULL, &fct, NULL) != 0)
			return (false);
	}
	i = 0;
	while (i < nbr)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (false);
	}
	return (true);
}
