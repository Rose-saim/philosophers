#include "philosophers.h"

void	print_thread(pthread_mutex_t *lock, char *str, t_philo *philo, float time)
{
	pthread_mutex_lock(lock);
	printf("%s ", str);
	printf("philo|%zu|%f|ms\n", philo->id, time);
	pthread_mutex_unlock(lock);
}

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void	end_pthread(t_lst_philo *lst_philo)
{
	int	i = 0;
	t_philo	*head;

	head = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{		
		pthread_join(head->thread, NULL);
		head = head->next;
		++i;
	}
}

void	*ft_sleep(t_philo *philo)
{
	float	time_past;

	usleep(philo->time_to_sleep*1e3);
	gettimeofday(&philo->time_end, NULL);
	time_past = time_diff(&philo->time_begin, &philo->time_end);
	print_thread(&philo->fork->mutex, "\033[0;32msleep", philo, time_past);
	return (NULL);
}

void	*ft_think(t_philo *philo)
{
	float	time_past;
	
	gettimeofday(&philo->time_end, NULL);
	time_past = time_diff(&philo->time_begin, &philo->time_end);
	print_thread(&philo->fork->mutex, "\033[0;37mthink", philo, time_past);
	return (NULL);
}


void	take_fork(int	fork_to_take, t_philo *philo)
{
	float	time_past;
	int		fork;

	if (philo->id == philo->last_philo)
		fork = 0;
	else
		fork = fork_to_take + 1;
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take]);
	pthread_mutex_lock(&philo->fork->tab_fork[fork]);
	usleep((philo->time_for_eat) * 1e3);
	gettimeofday(&philo->time_end, NULL);
	time_past = time_diff(&philo->time_begin, &philo->time_end);
	if (time_past < philo->time_bf_eat*1e-3)
	{
		print_thread(&philo->fork->mutex, "\033[1;33meat", philo, time_past);
		philo->nbr_time_eat -= 1;
	}
	else
	{
		print_thread(&philo->fork->mutex, "\033[0;31mis dead", philo, time_past);
		philo->sig->sig_dead = 0;
	}
	pthread_mutex_unlock(&philo->fork->tab_fork[fork]);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take]);
}


void	*eat(t_philo *philo)
{
	static	int i = 0;

	if ((philo->id % 2) == i)
	{
		usleep(philo->time_for_eat * 1e1);
		if (i == 0)
			i = 1;
		else
			i = 0;
	}
	take_fork(philo->id - 1, philo);
	return(NULL);
}

void	*event_loop(void *p)
{
	
	t_philo *philo;
	
	philo = (t_philo *)p;
	philo->sig->sig_dead = 1;
	while (1)
	{
		eat(philo);
		if (philo->nbr_time_eat == 0)
		{
			pthread_join(philo->thread, NULL);
			break ;
		}
		if (philo->sig->sig_dead == 0)
			return (NULL);
		gettimeofday(&philo->time_begin, NULL);
		ft_sleep(philo);
		if (philo->sig->sig_dead == 0)
			return (NULL);
		ft_think(philo);
		if (philo->sig->sig_dead == 0)
			return (NULL);
	}
	return (NULL);
}
