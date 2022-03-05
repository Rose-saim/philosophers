/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:56:47 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/03 12:26:58 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#define ERROR "Number of arguments is wrong"

void	*to_do(t_lst_philo *lst_philo)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		pthread_create(&(philo->thread), NULL, event_loop, philo);
		++i;
		philo = philo->next;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_lst_philo	lst_philo;
	t_fork		fork;
	t_sig		sig;

	if (ac != 5 && ac != 6)
	{
		write(2, ERROR, ft_strlen(ERROR));
		return (0);
	}
	parsing_argument(av);
	init_info_lst(ac, av, &lst_philo);
	init_fork(&fork, &lst_philo, lst_philo.nbr_philo);
	init_sig(&lst_philo, &sig);
	to_do(&lst_philo);
	free_destroy(&lst_philo);
	return (0);
}
