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
	int					is_dead;
	pthread_mutex_t		*tab_fork;
	pthread_mutex_t		mutex;
}t_fork;

typedef struct s_philo
{
	struct timeval		time_begin;
	struct timeval		time_end;
	unsigned int		time_bf_eat;
	unsigned int		time_for_eat;
	unsigned int		time_to_sleep;
	unsigned int		nbr_time_eat;
	int					dead;
	size_t				id;
	pthread_t			thread;
	t_fork				*fork;
	void			*lst_philo;
	struct s_philo		*next;
}t_philo;

typedef struct s_lst_philo
{
	t_philo	*begin;
	t_philo	*end;
	pthread_mutex_t		door;
	t_fork				*fork;
	int		nbr_philo;
}t_lst_philo;


int	ft_atoi(const char *str);
int	ft_strlen(char *str);

t_lst_philo	*creat_lst(t_lst_philo *lst_philo, int nbr_philo);
t_lst_philo	*lst_add(t_lst_philo *lst_philo, int i);
t_lst_philo	*init_mutex(t_fork *fork, t_lst_philo *philo, int nbr_philo);

void	add_info_lst(t_lst_philo *lst_philo, int info[]);

void	initilisation(int ac, char **av, t_lst_philo *lst_philo);

void	*eat(void *p);
void	*ft_think(t_philo *philo);
void	*ft_sleep(t_philo *philo);
void	take_fork(int 	fork_to_take, t_philo *philo);
void	*to_do(t_lst_philo *lst_philo);

void	parsing_argument(char **av);
void	write_error(char *str);
#endif