/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:35 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/28 18:35:35 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_(t_philo *philos)
{
	if ((philos->rules->eat_limit) >= 0 && ((philos->meal_count)
			>= (philos->rules->eat_limit)))
	{
		exit (300);
	}
	if ((get_time(&(philos->rules->timer)) * 1000)
		- ((philos->last_meal) * 1000) > (philos->rules->to_die))
	{
		safe_print_t_d('d', philos,
			get_time(&(philos->rules->timer)));
		exit (200);
	}
}

static void	routine(t_philo *philos)
{
	sem_wait(philos->fork->fork);
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	sem_wait(philos->fork->fork);
	safe_print_f_e_s('f', philos, get_time(&(philos->rules->timer)));
	(philos->meal_count) += 1;
	safe_print_f_e_s('e', philos, get_time(&(philos->rules->timer)));
	(philos->last_meal) = get_time(&(philos->rules->timer));
	ft_usleep((unsigned int)(philos->rules->to_eat));
	sem_post(philos->fork->fork);
	sem_post(philos->fork->fork);
	safe_print_f_e_s('s', philos, get_time(&(philos->rules->timer)));
	ft_usleep(philos->rules->to_sleep);
	safe_print_t_d('t', philos, get_time(&(philos->rules->timer)));
	check_(philos);
}

void	*philo_routine(void *ph)
{
	t_philo	*philos;

	philos = (t_philo *)ph;
	if ((philos->id) % 2 == 0)
	{
		ft_usleep((philos->rules->phs_nb) * 1000);
	}
	while (1)
	{
		routine(philos);
	}
	return (NULL);
}

void	start_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = rules->philos;
	gettimeofday(&(rules->timer.start_time), NULL);
	while (i < rules->phs_nb)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			philo_routine(philos + i);
		}
		i++;
		ft_usleep(100);
	}
}

void	wait_for_philos(t_rules *rules, int *result)
{
	int	i;

	i = -1;
	while (++i < rules->phs_nb)
	{
		waitpid(-1, result, 0);
		if (WIFEXITED(*result) && WEXITSTATUS(*result) == 200)
			break ;
	}
}
