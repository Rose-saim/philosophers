/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:57:33 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/03 14:20:43 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo)
{
	philo->color = "\033[0;32m";
	print_thread(&philo->fork->mutex, "is sleeping", philo);
	slp(philo->time_to_sleep * 1e3);
}

void	ft_think(t_philo *philo)
{
	philo->color = "\033[0;37m";
	print_thread(&philo->fork->mutex, "is thinking", philo);
}

void	eat(t_philo *philo)
{
	int		fork_right;

	fork_right = order_fork(philo);
	if (philo->id % 2 == 0)
		will_eat(philo);
	else
		will_eat(philo);
}

void	*event_loop(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if ((condition_event(eat, philo)) == 0
			|| philo->nbr_time_eat == 0)
			break ;
		// if (condition_event(ft_sleep, philo) == 0)
		// 	break ;
		// if (condition_event(ft_think, philo) == 0)
		// 	break ;
	}
	return (NULL);
}
