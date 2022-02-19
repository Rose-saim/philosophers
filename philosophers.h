#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_fork
{
	void				*philo;
	pthread_mutex_t		*tab_fork;
	pthread_mutex_t		door;
	unsigned int		time_for_eat;
}t_fork;

typedef struct s_philo
{
	struct timeval		time_begin;
	struct timeval		time_end;
	size_t				id;
	pthread_t			thread_eat;
	t_fork				*fork;
	unsigned int		time_bf_eat;
	struct s_philo		*next;
	int					dead;
}t_philo;

typedef struct s_lst_philo
{
	t_philo	*begin;
	t_philo	*end;
	int		signal;
}t_lst_philo;

struct    s_timeval  
{
  time_t        tv_sec ;   //used for seconds
  suseconds_t       tv_usec ;   //used for microseconds
}timeval;

int	ft_atoi(const char *str);
int	ft_strlen(char *str);

t_lst_philo	*creat_lst(t_lst_philo *lst_philo, int nbr_philo);
t_lst_philo	*lst_add(t_lst_philo *lst_philo, int i);
t_lst_philo	*init_mutex(t_fork *fork, t_lst_philo *philo, int nbr_philo);

void	*eat(t_philo *philo);
void	*ft_think(t_philo *philo);
void	*ft_sleep(t_philo *philo);
void	take_fork(int 	fork_to_take, t_philo *philo);

void	parsing_argument(char **av);
void	write_error(char *str);
#endif