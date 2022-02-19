#include "philosophers.h"

void	take_fork(int	fork_to_take, t_philo *philo)
{
	unsigned int	time_use;
	//Lock forks
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take]);
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take + 1]);
	//Philo eat
	usleep(philo->fork->time_for_eat);
	gettimeofday(&philo->time_end, NULL);
	time_use = philo->time_end.tv_usec - philo->time_begin.tv_usec;
	printf("BEGIN|%ld|END|%ld|\n", philo->time_begin.tv_usec, philo->time_end.tv_usec);
	printf("TIME_USE|%d|%zu\n", time_use, philo->id);
	//Print eat
	pthread_mutex_lock(&philo->fork->door);
	if (time_use < philo->time_bf_eat)
	{
		printf("\033[1;33m");
		printf("philo|%zu||eat|time|%ld|\n",philo->id, philo->time_end.tv_usec);
	}
	else
	{
		printf("\033[1;31m");
		printf("philo|%zu|id dead|time|%ld|\n",philo->id, philo->time_end.tv_usec);
		philo->dead = 1;
		exit(2);
	}
	pthread_mutex_unlock(&philo->fork->door);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take + 1]);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take]);
}

void	*eat(void *p)
{
	static int	i = 0;
	int			number_fork;
	t_philo *philo;

	philo = (t_philo *)p;
	if ((philo->id % 2) == i)
	{
		if (i == 0)
			i = 1;
		else
			i = 0;
	}
	gettimeofday(&philo->time_begin, NULL);
	number_fork = philo->id;
	take_fork(number_fork - 1, philo);
	ft_sleep(philo);
	return(NULL);
}

void	*ft_sleep(t_philo *philo)
{
	gettimeofday(&philo->time_end, NULL);
	pthread_mutex_lock(&philo->fork->door);
	printf("\033[0;35m");
	printf("philo|%zu|sleep|%ld|\n", philo->id, philo->time_end.tv_usec);
	pthread_mutex_unlock(&philo->fork->door);
	ft_think(philo);
	return (NULL);
}

void	*ft_think(t_philo *philo)
{
	gettimeofday(&philo->time_end, NULL);
	pthread_mutex_lock(&philo->fork->door);
	printf("\033[0;32m");
	printf("philo|%zu|think|%ld|\n", philo->id, philo->time_end.tv_usec);
	pthread_mutex_unlock(&philo->fork->door);
	eat((void *)philo);
	return (NULL);
}

void	*to_do(t_lst_philo *lst_philo)
{
	t_philo		*philo;
	size_t			i = 0;

	philo = lst_philo->begin;
	while (i <= lst_philo->end->id)
	{
		philo->next->time_bf_eat = philo->time_bf_eat;
		pthread_create(&philo->thread_eat, NULL, eat, (void*)philo);
		if (philo->dead == 1)
		{
			end_pthread(lst_philo->begin, lst_philo->end->id);
			exit(2);
		}
		++i;
		philo = philo->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_lst_philo	lst_philo;
	t_philo	*head;
	t_fork	fork;

	
	if (ac != 5 && ac != 6)
		write_error("Number of arguments is wrong");
	parsing_argument(av);
	//NBR philo
	int	nbr_philo;
	nbr_philo = ft_atoi(av[1]);
	fork.time_for_eat = ft_atoi(av[3]);
	//Create list philo
	lst_philo.begin = NULL;
	lst_philo.end = NULL;
	creat_lst(&lst_philo, nbr_philo);
	head = lst_philo.begin;
	//During before eat
	head->time_bf_eat = ft_atoi(av[2]);
	//Time for eat
	//Init stock thread
	pthread_mutex_init(&fork.door, NULL);
	init_mutex(&fork, &lst_philo, nbr_philo);
	// Create pthread
 	// while (1)
	// {
		to_do(&lst_philo);
		// head = head->next;
	// }
	//Wait end pthread
	end_pthread(lst_philo.begin, lst_philo.end->id);
	return (0);
}