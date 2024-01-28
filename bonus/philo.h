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
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define YES 1
# define NO 0

# define PH_MAX 200

# define ERROR_MG "\nSomthing is wrong with the arguments\n\t   ( •͡˘ _•͡˘)ノð\n"
# define ERROR_MG2 "\t   USE : -help   \n"
# define CORRECT_MG "\nMUST BE ALL POSITIVE NUMBERS\nTHE VALUE MUST FIT IN INT"
# define CORRECT_MG2 "Use Your Common Sense -_-\n"
# define ANSI_COLOR_RED     "\033[0;91m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct s_rules
{
	sem_t			*forks;
	sem_t			*write;
	sem_t			*death;
	sem_t			*stop;
	unsigned int	start;
	int				philo_numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_max;
	int				max_eat;
	int				eat_counter;
}				t_rules;

typedef struct s_philo
{
	t_rules	*data;
	pid_t			pid;
	unsigned int	eating_time;
	unsigned int	next_meal;
	int				index;
	int				is_dead;
	int				eat_max;
	int				meal_count;
}				t_philo;

//===========_INPUT_============//
size_t	ft_atoi(const char *str);
bool	is_valid(char **av, int ac);
int		error_(char *str);
//===========_UTILS_============//
int				init_(char **av, int ac, t_rules *rules);
void			ft_usleep(unsigned int usec);
unsigned int	get_time(void);
void			start_process(t_rules *rules, t_philo *philo);
void			safe_print_f_e_s(char c, t_philo *philos, unsigned int ts);
void			safe_print_t_d(char c, t_philo *philos, unsigned int ts);
t_philo			*ft_philo_init(t_rules *rules);
void			create_semaphores(t_rules *rules);

#endif