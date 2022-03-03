/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:44:15 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/03 12:21:17 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	while (i < nbr_philo)
	{
		++i;
		(philo->sig) = sig;
		philo = philo->next;
	}
	pthread_mutex_init(&(sig->is_dead), NULL);
	(sig->sig_dead) = 1;
}

t_lst_philo	*init_fork(t_fork *fork, t_lst_philo *lst_philo, int nbr_philo)
{
	int		i;
	t_philo	*head;

	fork->tab_fork = malloc(sizeof(pthread_mutex_t) * (nbr_philo));
	if (!fork->tab_fork)
		return (NULL);
	i = 0;
	while (i < nbr_philo)
		pthread_mutex_init(&(fork->tab_fork[i++]), NULL);
	pthread_mutex_init(&(fork->mutex), NULL);
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
