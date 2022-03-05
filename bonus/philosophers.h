/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:48:49 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/04 19:50:30 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_fork
{
	void			*philo;
	sem_t	tab_fork;
	sem_t	mutex;
}t_fork;

typedef struct s_sig
{
	int				sig_dead;
	int				sig_eat;
	int				even_max_eat[2];
	int				odd_max_eat[2];
	sem_t	is_dead;
	sem_t	change_sig;
}t_sig;

typedef struct s_philo
{
	long			time_begin;
	long			t_beg_lp;
	long			time_end;
	void			*lst_philo;
	unsigned int	time_bf_eat;
	unsigned int	time_for_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_time_eat;
	char			*color;
	size_t			id;
	size_t			last_philo;
	pthread_t		thread;
	t_fork			*fork;
	t_sig			*sig;
	int				dead;
	struct s_philo	*next;
}t_philo;

typedef struct s_lst_philo
{
	t_philo	*begin;
	t_philo	*end;
	t_fork	*fork;
	int		nbr_philo;
}t_lst_philo;

int			ft_atoi(const char *str);
int			ft_strlen(char *str);
long		ft_time(void);

int			condition_event(void (*f)(t_philo*), t_philo *philo);
int			if_dead(t_philo *philo);
int			order_fork(t_philo *philo);

void		lock(t_philo *philo);
void		unlock(t_philo *philo);
void		print_thread(sem_t *l, char *s, t_philo *ph);

long		time_diff(t_philo *philo);

t_lst_philo	*creat_lst(t_lst_philo *lst_philo, int nbr_philo);
t_lst_philo	*lst_add(t_lst_philo *lst_philo, int i);
t_lst_philo	*init_fork(t_fork *fork, t_lst_philo *philo, int nbr_philo);

void		add_info_lst(t_lst_philo *lst_philo, int info[]);
void		free_lst_philo(t_lst_philo *lst_philo);

void		init_info_lst(int ac, char **av, t_lst_philo *lst_philo);
void		init_sig(t_lst_philo *lst_philo, t_sig *sig);

void		eat(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		slp(long nbr);

void		take_fork(t_philo *philo);
void		philo_is_eating(t_philo *philo);
void		philo_is_dead(t_philo *philo, long time_past);

void		*event_loop(void *p);
void		*to_do(t_lst_philo *lst_philo);
void		will_eat(t_philo *philo, int fork_first, int fork_second);

void		free_destroy(t_lst_philo *lst_philo);
void		end_pthread(t_lst_philo *lst_philo);
void		destroy_mutex(t_lst_philo *lst_philo);

void		parsing_argument(char **av);
void		write_error(char *str);

#endif
