/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:50 by muel-bak          #+#    #+#             */
/*   Updated: 2024/02/01 13:34:40 by muel-bak         ###   ########.fr       */
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
# include <sys/time.h>

//===========_MACROS_============//
# define PH_MAX 200
# define ERROR_MG "\nSomthing is wrong with the arguments\n\t   ( •͡˘ _•͡˘)ノð\n"
# define ERROR_MG2 "\t   USE : -help   \n"
# define CORRECT_MG "\nMUST BE ALL POSITIVE NUMBERS\nTHE VALUE MUST FIT IN INT"
# define CORRECT_MG2 "Use Your Common Sense -_-\n"
# define ANSI_COLOR_RED     "\033[0;91m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_RESET   "\x1b[0m"
//===========_STRUCTS_===========//
typedef struct s_rules	t_rules;
typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_timer
{
	struct timeval	start_time;
}	t_timer;

typedef struct s_philo
{
	long			meal_count;
	pthread_mutex_t	ml_ct_mtx;
	long			last_meal;
	pthread_mutex_t	lst_ml_mtx;
	bool			*all_alive;
	t_fork			*r_fork;
	t_fork			*l_fork;
	pthread_t		th;
	int				id;
	bool			start;
	t_rules			*rules;
}	t_philo;

typedef struct s_sudo
{
	int			sudo_id;
	t_philo		*philos;
	pthread_t	th;
}	t_sudo;

struct s_rules
{
	long			phs_nb;
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
	size_t			time;
	t_timer			timer;
	long			keep_time;
	pthread_mutex_t	full_mtx;
	long			full;
	long			eat_limit;
	long			start;
	pthread_mutex_t	alive_mutex;
	bool			all_alive;
	t_fork			*forks;
	t_philo			*philos;
	t_sudo			sudo;
	pthread_mutex_t	write_mutex;
};

//===========_INPUT_============//
size_t	ft_atoi(const char *str);
bool	is_valid(char **av, int ac);
int		error_(char *str);
//===========_UTILS_============//
bool	init_rules(t_rules *rules, char **av, int ac);
void	start_philos(t_rules *rules);
void	wait_for_philos(t_rules *rules);
void	safe_print_t_d(char c, t_philo *philos, unsigned int ts);
void	safe_print_f_e_s(char c, t_philo *philos, unsigned int ts);
void	ft_usleep(unsigned int usec);
size_t	get_time(t_timer *timer);
void	*sudo_routine(void *sdo);

#endif
