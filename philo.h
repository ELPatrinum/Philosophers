/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:50 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/18 22:20:52 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>

//===========_MACROS_============//
# define PH_MAX 200
# define ERROR_MG "\nSomthing is wrong with the arguments\n\t   ( •͡˘ _•͡˘)ノð\n"
# define ERROR_MG2 "\t   USE : -help   \n"
# define CORRECT_MG "\nMUST BE ALL POSITIVE NUMBERS\nTHE VALUE MUST FIT IN INT"
# define CORRECT_MG2 "Use Your Common Sense -_-\n"
# define ANSI_COLOR_RED     "\033[0;91m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
//===========_STRUCTS_===========//
typedef struct s_rules	t_rules;
typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	long		meal_count;
	long		last_meal;
	bool		full;
	bool		*all_alive;
	t_fork		*r_fork;
	t_fork		*l_fork;
	pthread_t	th;
	int			id;
	t_rules		*rules;
}	t_philo;

struct s_rules
{
	size_t		phs_nb;
	size_t		to_die;
	size_t		to_eat;
	size_t		to_sleep;
	long		eat_limit;
	long		start;
	bool		all_alive;
	t_fork		*forks;
	t_philo		*philos;
};
//===========_INPUT_============//
size_t	ft_atoi(const char *str);
bool	is_valid(char **av, int ac);
int	error_(char *str);
//===========_UTILS_============//
void	init_rules(t_rules *rules, char **av, int ac);

#endif