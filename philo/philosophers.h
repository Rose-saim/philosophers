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

typedef struct	s_sig
{
	int	sig_dead;
}t_sig;

typedef struct s_philo
{
	struct timeval		time_begin;
	struct timeval		time_end;
	void				*lst_philo;
	unsigned int		time_bf_eat;
	unsigned int		time_for_eat;
	unsigned int		time_to_sleep;
	unsigned int		nbr_time_eat;
	char				*color;
	size_t				id;
	size_t				last_philo;
	pthread_t			thread;
	t_fork				*fork;
	t_sig				*sig;
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

float time_diff(t_philo *philo, struct timeval *start, struct timeval *end);

t_lst_philo	*creat_lst(t_lst_philo *lst_philo, int nbr_philo);
t_lst_philo	*lst_add(t_lst_philo *lst_philo, int i);
t_lst_philo	*init_mutex(t_fork *fork, t_lst_philo *philo, int nbr_philo);

void	add_info_lst(t_lst_philo *lst_philo, int info[]);
void	free_lst_philo(t_lst_philo *lst_philo);

void	init_info(int ac, char **av, t_lst_philo *lst_philo);
void	init_sig(t_lst_philo *lst_philo);

void	*eat(t_philo *philo);
void	*ft_think(t_philo *philo);
void	*ft_sleep(t_philo *philo);

void	lock_fork(t_philo *philo, int fork);
void	philo_is_eating(t_philo *philo, int time_past);
void	philo_is_dead(t_philo *philo, int time_past);


void	*event_loop(void *p);
void	*to_do(t_lst_philo *lst_philo);
void	take_fork(int 	fork_to_take, t_philo *philo);

void	end_pthread(t_lst_philo *lst_philo);
void    destroy_mutex(t_lst_philo *lst_philo);

void	print_thread(pthread_mutex_t *lock, char *str, t_philo *philo, float time);

void	parsing_argument(char **av);
void	write_error(char *str);
#endif