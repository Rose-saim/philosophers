#include "philosophers.h"

void	free_destroy(t_lst_philo *lst_philo)
{
	end_pthread(lst_philo);
    destroy_mutex(lst_philo);
    free_lst_philo(lst_philo);
}

void	*ok()
{
	return (NULL);
}

void	*to_do(t_lst_philo *lst_philo)
{
	t_philo		*philo;
	int			i = 0;

	philo = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		pthread_create(&philo->thread, NULL, event_loop, (void*)(philo));
		printf("id|%zu|is create\n", philo->id);
		++i;
		philo = philo->next;
	}
	free_destroy(lst_philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_lst_philo	lst_philo;
	t_fork	fork;
	
	if (ac != 5 && ac != 6)
		write_error("Number of arguments is wrong");
	parsing_argument(av);
	init_info(ac, av, &lst_philo);
	init_mutex(&fork, &lst_philo, lst_philo.nbr_philo);
	init_sig(&lst_philo);
	to_do(&lst_philo);
	return (0);
}