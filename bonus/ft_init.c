#include "philosophers.h"

void	init_info(int ac, char **av, t_lst_philo *lst_philo)
{
	t_philo	*philo;
	int		info[4];

	philo = NULL;
	lst_philo->nbr_philo = ft_atoi(av[1]);
	if (lst_philo->nbr_philo == 1)
		write_error("Philo is dead");
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

t_lst_philo	*init_mutex(t_fork *fork, t_lst_philo *lst_philo, int nbr_philo)
{
	int	i;
	t_philo	*head;

	i = 0;
	head = lst_philo->begin;
	sem_init(&(fork->mutex), 0, 1);
	sem_init(&(fork->tab_fork), 0, nbr_philo);
	(lst_philo->fork) = fork;
	i = 0;
	while (i < lst_philo->nbr_philo)
	{
		head->fork = fork;
		head = head->next;
		++i;
	}
	return (lst_philo);
}
