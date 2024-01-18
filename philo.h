/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:50 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/17 16:13:21 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>

//===========_MACROS_============//
#define PH_MAX 200
//===========_STRUCTS_===========//
typedef struct s_philo
{
	size_t		phs_nb;
	size_t		to_die;
	size_t		to_eat;
	size_t		to_sleep;
	size_t		eat_limit;
	bool		eating;
	bool		*dead;
	pthread_t	th;
	int			id;
}	t_philo;

//===========_INPUT_============//
size_t	ft_atoi(const char *str);
bool	is_valid(char **av, int ac);
int		print_error(void);
void	init_philo(t_philo *philo, bool check, char **av);

#endif