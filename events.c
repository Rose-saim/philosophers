#include "philosophers.h"

// void	*ft_sleep(t_philo *philo)
// {
// 	gettimeofday(&philo->time_end, NULL);
// 	pthread_mutex_lock(&philo->fork->door);
// 	printf("\033[0;35m");
// 	printf("philo|%zu|sleep|%ld|\n", philo->id, philo->time_end.tv_usec);
// 	pthread_mutex_unlock(&philo->fork->door);
// 	ft_think(philo);
// 	return (NULL);
// }

// void	*ft_think(t_philo *philo)
// {
// 	gettimeofday(&philo->time_end, NULL);
// 	pthread_mutex_lock(&philo->fork->door);
// 	printf("\033[0;32m");
// 	printf("philo|%zu|think|%ld|\n", philo->id, philo->time_end.tv_usec);
// 	pthread_mutex_unlock(&philo->fork->door);
// 	eat((void *)philo);
// 	return (NULL);
// }

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
	(void)fork_to_take;
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take]);
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take + 1]);
	pthread_mutex_lock(&philo->fork->mutex);
	printf("\033[1;33m");
	printf("id|%zu|time_use|%d|\n", philo->id,philo->time_bf_eat);
	pthread_mutex_unlock(&philo->fork->mutex);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take + 1]);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take]);
}

void	*eat(void *p)
{
	t_philo *philo;
	philo = (t_philo *)p;
	take_fork(philo->id - 1, philo);
	return(NULL);
}


void	*to_do(t_lst_philo *lst_philo)
{
	// t_fork	fork;
	t_philo		*philo;
	int			i = 0;

	// (lst_philo->fork) = &fork;
	// init_mutex(&fork, lst_philo, lst_philo->nbr_philo);
	philo = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		// philo->fork = &fork;
		pthread_create(&philo->thread, NULL, eat, (void*)(philo));
		++i;
		philo = philo->next;
	}
	end_pthread(lst_philo);
	return (0);
}