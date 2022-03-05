/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:44:15 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/04 19:53:23 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#define RESERVE 1

void	init_info_lst(int ac, char **av, t_lst_philo *lst_philo)
{
	int		info[4];

	lst_philo->nbr_philo = ft_atoi(av[1]);
	if (lst_philo->nbr_philo == 1)
	{
		printf("%ld 1 is dead\n", ft_time() - ft_time());
		exit (1);
	}
	info[0] = ft_atoi(av[2]);
	info[1] = ft_atoi(av[3]);
	info[2] = ft_atoi(av[4]);
	if (ac == 6)
		info[3] = ft_atoi(av[5]);
	else
		info[3] = -1;
	creat_lst(lst_philo, lst_philo->nbr_philo);
	add_info_lst(lst_philo, info);
}

void	init_sig(t_lst_philo *lst_philo, t_sig *sig)
{
	int		nbr_philo;
	int		i;
	t_philo	*philo;

	i = 0;
	philo = lst_philo->begin;
	nbr_philo = lst_philo->nbr_philo;
	sig->even_max_eat[RESERVE] = nbr_philo / 2;
	sig->even_max_eat[0] = sig->even_max_eat[RESERVE];
	if (nbr_philo % 2 == 0)
		sig->odd_max_eat[RESERVE] = sig->even_max_eat[RESERVE];
	else
		sig->odd_max_eat[RESERVE] = sig->even_max_eat[RESERVE] + 1;
	sig->odd_max_eat[0] = sig->odd_max_eat[RESERVE];
	sig->sig_eat = 2;
	while (i < nbr_philo)
	{
		++i;
		(philo->sig) = sig;
		philo = philo->next;
	}
	sem_init(&(sig->is_dead), 0, 1);
	sem_init(&(sig->change_sig), 0, 1);
	(sig->sig_dead) = 1;
}

t_lst_philo	*init_fork(t_fork *fork, t_lst_philo *lst_philo, int nbr_philo)
{
	int		i;
	t_philo	*head;

	sem_init(&(fork->tab_fork), 0, nbr_philo);
	sem_init(&(fork->mutex), 0, 1);
	i = 0;
	head = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		++i;
		(head->fork) = fork;
		head = head->next;
	}
	(lst_philo->fork) = fork;
	return (lst_philo);
}
