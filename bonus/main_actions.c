/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:57:33 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/04 20:53:13 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo)
{
	philo->color = "\033[0;32m";
	print_thread(&philo->fork->mutex, "is sleeping", philo);
	slp(philo->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	philo->color = "\033[0;37m";
	print_thread(&philo->fork->mutex, "is thinking", philo);
}

int	update_signal(t_philo *philo)
{
	sem_wait(&philo->sig->change_sig);
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
	sem_post(&philo->sig->change_sig);
	return (1);
}


void __eat(t_philo *philo)
{
	lock(philo);
	take_fork(philo);
	if (update_signal(philo) == 1)
	{
		long	past_time;
		
		past_time = ft_time() - philo->t_beg_lp;
		if (past_time <= philo->time_bf_eat)
			philo_is_eating(philo);
		else
			philo_is_dead(philo, past_time);
	}
	unlock(philo);
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
		if (if_dead(philo) == 1 || philo->nbr_time_eat == 0)
			break ;	
		sem_wait(&philo->sig->change_sig);
		if (
			(philo->id % 2 == 0 && philo->sig->sig_eat == 2)
			||(philo->id % 2 != 0 && philo->sig->sig_eat != 2)
			)
		{
			sem_post(&philo->sig->change_sig);
			__eat(philo);
		}
		else
			sem_post(&philo->sig->change_sig);
	}
	return (NULL);
}
