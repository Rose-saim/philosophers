#include "philosophers.h"

void	take_fork(int	fork_to_take, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take]);
	pthread_mutex_lock(&philo->fork->tab_fork[fork_to_take + 1]);
	pthread_mutex_lock(&philo->fork->door);
	printf("philo|%zu||eat|%d|%d|\n",philo->id, fork_to_take, fork_to_take + 1);
	pthread_mutex_unlock(&philo->fork->door);
	sleep(1);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take + 1]);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take]);
}

void	*eat(void *p)
{
	t_philo*		philo;
	int			number_fork;

	philo = (t_philo*)p;
	number_fork = philo->id;
	if (philo->id %2 == 0)
		take_fork(number_fork - 1, philo);
	else
	{
		while (1)
		{
			if (signal == 1)
				take_fork(number_fork - 1, philo);
		}
	}
	pthread_exit (NULL);
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
	//Create list philo
	lst_philo.begin = NULL;
	lst_philo.end = NULL;
	lst_philo.size = nbr_philo;
	creat_lst(&lst_philo, nbr_philo);
	//Init stock thread
	pthread_mutex_init(&fork.door, NULL);
	init_mutex(&fork, &lst_philo, nbr_philo);
	// Create pthread
	head = lst_philo.begin;
	while (head->id != lst_philo.end->id)
	{
		pthread_create(&head->thread_stock, NULL, eat, (void*)head);
		head = head->next;
	}
	head = lst_philo.begin;
	//Wait end pthread]
	while (head->id != lst_philo.end->id)
	{
		pthread_join(head->thread_stock, NULL);
		head = head->next;
	}
	return (0);
}