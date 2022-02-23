#include "philosophers.h"


void	initilisation(char **av, t_lst_philo *lst_philo)
{
	t_philo	*philo;
	int		time_bf_eat;
	int		time_for_eat;

	philo = NULL;
	philo = lst_philo->begin;
	lst_philo->nbr_philo = ft_atoi(av[1]);
	time_bf_eat = ft_atoi(av[2]);
	time_for_eat = ft_atoi(av[3]);
	creat_lst(lst_philo, lst_philo->nbr_philo);
	add_info_lst(lst_philo, time_bf_eat, time_for_eat);
}

int	main(int ac, char **av)
{
	t_lst_philo	lst_philo;
	t_fork	fork;
	
	if (ac != 5 && ac != 6)
		write_error("Number of arguments is wrong");
	parsing_argument(av);
	initilisation(av, &lst_philo);
	init_mutex(&fork, &lst_philo, lst_philo.nbr_philo);
	to_do(&lst_philo);
	return (0);
}