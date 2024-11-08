/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:44 by muel-bak          #+#    #+#             */
/*   Updated: 2024/02/01 10:38:46 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>

# define PH_MAX 200

# define ERROR_MG "\nSomthing is wrong with the arguments\n\t   ( •͡˘ _•͡˘)ノð\n"
# define ERROR_MG2 "\t   USE : -help   \n"
# define CORRECT_MG "\nMUST BE ALL POSITIVE NUMBERS\nTHE VALUE MUST FIT IN INT"
# define CORRECT_MG2 "Use Your Common Sense -_-\n"
# define ANSI_COLOR_RED     "\033[0;91m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct s_rules	t_rules;

typedef struct s_timer
{
	struct timeval	start_time;
}	t_timer;

typedef struct s_forks
{
	sem_t	*fork;
}	t_fork;

typedef struct s_philo
{
	long			meal_count;
	long			last_meal;
	t_fork			*fork;
	pid_t			pid;
	int				id;
	bool			start;
	t_rules			*rules;
}	t_philo;

struct s_rules
{
	long			phs_nb;
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
	size_t			time;
	t_timer			timer;
	long			keep_time;
	long			full;
	long			eat_limit;
	long			start;
	t_fork			*forks;
	t_philo			*philos;
	sem_t			*write_sem;
};

//===========_INPUT_============//
size_t	ft_atoi(const char *str);
bool	is_valid(char **av, int ac);
int		error_(char *str);
void	if_one(char **av);
//===========_UTILS_============//
bool	init_rules(t_rules *rules, char **av, int ac);
void	start_philos(t_rules *rules);
void	safe_print_t_d(char c, t_philo *philos, unsigned int ts);
void	safe_print_f_e_s(char c, t_philo *philos, unsigned int ts);
void	ft_usleep(unsigned int usec, t_philo *philos, int check);
size_t	get_time(t_timer *timer);
void	*sudo_routine(void *sdo);
void	wait_for_philos(t_rules *rules, int *result);

#endif
