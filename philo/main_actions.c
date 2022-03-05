/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:57:33 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/05 21:02:11 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo)
{
	if (if_dead(philo) == 1)
		return ;
	philo->color = "\033[0;32m";
	print_thread(&philo->fork->mutex, "is sleeping", philo);
	slp(philo->time_to_sleep, philo);
}

void	ft_think(t_philo *philo)
{
	if (if_dead(philo) == 1)
		return ;
	philo->color = "\033[0;37m";
	print_thread(&philo->fork->mutex, "is thinking", philo);
}

int	update_signal(t_philo *philo)
{
	pthread_mutex_lock(&philo->sig->change_sig);
	if (philo->id % 2 == 0)
	{
		if (philo->sig->even_max_eat[0] > 0)
			philo->sig->even_max_eat[0] -= 1;
		if (philo->sig->even_max_eat[0] == 0)
		{
			philo->sig->even_max_eat[0] = philo->sig->even_max_eat[1];
			philo->sig->sig_eat = 0;
		}
	}
	else
	{
		if (philo->sig->odd_max_eat[0] > 0)
			philo->sig->odd_max_eat[0] -= 1;
		if (philo->sig->odd_max_eat[0] == 0)
		{
			philo->sig->odd_max_eat[0] = philo->sig->odd_max_eat[1];
			philo->sig->sig_eat = 2;
		}
	}
	pthread_mutex_unlock(&philo->sig->change_sig);
	return (1);
}

void	__eat(t_philo *philo)
{
	int	fork_right;

	fork_right = order_fork(philo);
	if (philo->id % 2 == 0)
		will_eat(philo, fork_right, philo->id - 1);
	else
		will_eat(philo, philo->id - 1, fork_right);
	if (if_dead(philo) == 1)
		return ;
	ft_sleep(philo);
	ft_think(philo);
	return ;
}

void	*event_loop(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if (if_dead(philo) == 1
			|| philo->nbr_time_eat == 0)
			break ;
		pthread_mutex_lock(&philo->sig->change_sig);
		if ((philo->id % 2 == 0 && philo->sig->sig_eat == 2)
			|| (philo->id % 2 != 0 && philo->sig->sig_eat != 2))
		{
			pthread_mutex_unlock(&philo->sig->change_sig);
			__eat(philo);
		}
		else
			pthread_mutex_unlock(&philo->sig->change_sig);
	}
	return (NULL);
}
