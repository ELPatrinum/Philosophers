/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:35 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/28 16:20:34 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*is_dead(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->death);
		if (philo->next_meal < get_time() && ((philo->data->eat_max != -1)
				&& (philo->meal_count < philo->data->eat_max)))
		{
			safe_print_t_d('d', philo, (get_time() - philo->data->start));
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if ((philo->data->eat_max != -1)
			&& (philo->data->eat_counter == philo->data->max_eat))
		{
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
	}
	return (NULL);
}

static void	philo_routine(t_philo *philo)
{
	pthread_t	sudo;

	philo->next_meal = get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&sudo, NULL, is_dead, philo);
	pthread_detach(sudo);
	while (1)
	{
		sem_wait(philo->data->forks);
		safe_print_f_e_s('f', philo, (get_time() - philo->data->start));
		sem_wait(philo->data->forks);
		safe_print_f_e_s('f', philo, (get_time() - philo->data->start));
		safe_print_f_e_s('e', philo, (get_time() - philo->data->start));
		if (philo->data->eat_max != -1)
			philo->data->eat_counter++;
		ft_usleep(philo->data->time_to_eat * 1000);
		(philo->meal_count)++;
		philo->eating_time = get_time();
		philo->next_meal = philo->eating_time
			+ (unsigned int)philo->data->time_to_die;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		safe_print_f_e_s('s', philo, (get_time() - philo->data->start));
		ft_usleep(philo->data->time_to_sleep * 1000);
		safe_print_t_d('t', philo, (get_time() - philo->data->start));
	}
}

void	start_process(t_rules *rules, t_philo *philo)
{
	int	i;

	i = 0;
	rules->start = get_time();
	while (i < rules->philo_numbers)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo_routine(philo + i);
			exit(0);
		}
		i++;
		ft_usleep(100);
	}
}
