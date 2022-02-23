#include "philosophers.h"

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void	*ft_sleep(t_philo *philo)
{
	float	time_past;

	usleep(philo->time_to_sleep);
	gettimeofday(&philo->time_end, NULL);
	time_past = time_diff(&philo->time_begin, &philo->time_end);
	pthread_mutex_lock(&philo->fork->mutex);
	printf("\033[0;32mphilo|%zu|sleep|%f|\n", philo->id, time_past);
	pthread_mutex_unlock(&philo->fork->mutex);
	ft_think(philo);
	return (NULL);
}

void	*ft_think(t_philo *philo)
{
	float	time_past;

	gettimeofday(&philo->time_begin, NULL);
	gettimeofday(&philo->time_end, NULL);
	time_past = time_diff(&philo->time_begin, &philo->time_end);
	pthread_mutex_lock(&philo->fork->mutex);
	printf("\033[0;37mphilo|%zu|think|%f|\n", philo->id, time_past);
	pthread_mutex_unlock(&philo->fork->mutex);
	eat((void *)philo);
	return (NULL);
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

void	take_fork(int	fork_to_take, t_philo *philo)
{
	float	time_past;
	
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take]);
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take + 1]);
	usleep(philo->time_for_eat);
	gettimeofday(&philo->time_end, NULL);
	time_past = time_diff(&philo->time_begin, &philo->time_end);
	pthread_mutex_lock(&philo->fork->mutex);
	if (time_past < philo->time_bf_eat*1e-3)
	{
		printf("\033[1;33mphilo|%zu|time used|%f|\n", philo->id, philo->time_bf_eat*1e-3);
		philo->nbr_time_eat -= 1;
	}
	else
	{
		printf("\033[0;31mphilo|%zu|is dead|%f|\n", philo->id, time_past);
		philo->dead = 1;
		return ;
	}
	pthread_mutex_unlock(&philo->fork->mutex);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take + 1]);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take]);
}

void	*eat(void *p)
{
	t_philo *philo;
	philo = (t_philo *)p;
	if (philo->fork->is_dead == 1)
	{
		printf("id|%d|is dead\n", philo->fork->is_dead);
		return (NULL);
	}
	else
	{
		printf("id|%d|is dead\n", philo->fork->is_dead);
	}
	if (philo->nbr_time_eat == 0)
	{
		philo->fork->is_dead = 1;
		return (NULL);
	}
	take_fork(philo->id - 1, philo);
	if (philo->dead == 0)
		ft_sleep(philo);
	return(NULL);
}


void	*to_do(t_lst_philo *lst_philo)
{
	t_philo		*philo;
	int			i = 0;

	philo = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		pthread_create(&philo->thread, NULL, eat, (void*)(philo));
		++i;
		philo = philo->next;
	}
	puts("end");
	// exit(2);
	end_pthread(lst_philo);
	return (0);
}