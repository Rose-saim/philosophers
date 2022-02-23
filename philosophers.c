#include "philosophers.h"


void	initilisation(int ac, char **av, t_lst_philo *lst_philo)
{
	t_philo	*philo;
	int		info[4];

	philo = NULL;
	lst_philo->nbr_philo = ft_atoi(av[1]);
	info[0] = ft_atoi(av[2]);
	info[1] = ft_atoi(av[3]);
	info[2] = ft_atoi(av[4]);
	if (ac == 6)
		info[3] = ft_atoi(av[5]);
	else
		info[3] = -1;
	creat_lst(lst_philo, lst_philo->nbr_philo);
	add_info_lst(lst_philo, info);
	philo = lst_philo->begin;
}

void	init_sig(t_lst_philo *lst_philo)
{
	int	nbr_philo;
	int	i;
	t_philo	*philo;
	t_sig	sig;

	i = 0;
	sig.sig_dead = 1;
	philo = lst_philo->begin;
	nbr_philo = lst_philo->nbr_philo;
	while (i < nbr_philo)
	{
		philo->sig = &sig;
		philo = philo->next;
		++i;
	}
}

int	main(int ac, char **av)
{
	t_lst_philo	lst_philo;
	t_fork	fork;
	
	if (ac != 5 && ac != 6)
		write_error("Number of arguments is wrong");
	parsing_argument(av);
	initilisation(ac, av, &lst_philo);
	init_mutex(&fork, &lst_philo, lst_philo.nbr_philo);
	init_sig(&lst_philo);
	to_do(&lst_philo);
	return (0);
}