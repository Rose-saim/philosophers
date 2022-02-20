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
	printf("id|%zu|time_use|%d|\n", philo->id,philo->time_bf_eat);
}

void	*eat(void *p)
{
	t_fork *door;

	door = (t_fork *)p;
	pthread_mutex_lock(&door->mutex);
	printf("\033[1;33m");
	puts("lol");
	pthread_mutex_unlock(&door->mutex);
	// printf("id|%d|\n", fork->time_for_eat);
	// take_fork(philo->id - 1, philo);
	return(NULL);
}


void	*to_do(t_lst_philo *lst_philo)
{
	t_philo		*philo;
	int			i = 0;

	printf("%p\n", &lst_philo->fork);
	philo = lst_philo->begin;
	while (i < 5)
	{
		pthread_create(&philo->thread, NULL, eat, &lst_philo->fork);
		++i;
		philo = philo->next;
	}
	end_pthread(lst_philo);
	return (0);
}

void	add_info_lst(t_lst_philo *lst_philo, int time_bf_eat)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		philo->time_bf_eat = time_bf_eat;
		philo = philo->next;
		++i;
	}
}

void	initilisation(char **av, t_lst_philo *lst_philo)
{
	t_fork	fork;
	int		time_bf_eat;

	lst_philo->nbr_philo = ft_atoi(av[1]);
	time_bf_eat = ft_atoi(av[2]);
	fork.time_for_eat = ft_atoi(av[3]);
	creat_lst(lst_philo, lst_philo->nbr_philo);
	add_info_lst(lst_philo, time_bf_eat);
	printf("%p\n", &lst_philo->fork);
	init_mutex(&fork, lst_philo, lst_philo->end->id);
}


int	main(int ac, char **av)
{
	t_lst_philo	lst_philo;

	if (ac != 5 && ac != 6)
		write_error("Number of arguments is wrong");
	parsing_argument(av);
	initilisation(av, &lst_philo);
	to_do(&lst_philo);
	return (0);
}