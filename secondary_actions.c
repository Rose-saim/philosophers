/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:54:16 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/03 14:39:09 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork(t_philo *philo)
{
	philo->color = "\033[0;36m";
	print_thread(&philo->fork->mutex, "has taken a fork", philo);
	print_thread(&philo->fork->mutex, "has taken a fork", philo);
}

void	slp(long nbr)
{
	while (nbr > 0)
	{
		usleep(100*1e3);
		nbr -= 100;
	}
}

void	philo_is_eating(t_philo *philo)
{
	philo->color = "\033[1;33m";
	print_thread(&philo->fork->mutex, "is eating", philo);
	philo->t_beg_lp = ft_time();
	slp(philo->time_for_eat);
	philo->nbr_time_eat -= 1;
}

void	philo_is_dead(t_philo *philo, long time_past)
{
	pthread_mutex_lock(&philo->sig->is_dead);
	if (philo->sig->sig_dead == 1)
	{
		time_past = time_diff(philo) * 1e2;
		pthread_mutex_lock(&philo->fork->mutex);
		printf("\033[0;31m%ld %zu died", time_past, philo->id);
		pthread_mutex_unlock(&philo->fork->mutex);
		philo->sig->sig_dead = 0;
	}
	pthread_mutex_unlock(&philo->sig->is_dead);
}

void	will_eat(t_philo *philo, int fork_first, int fork_second)
{
	long	time_past;

	lock(philo, fork_first, fork_second);
	take_fork(philo);
	time_past = ft_time() - philo->t_beg_lp;
	if (time_past < philo->time_bf_eat)
		philo_is_eating(philo);
	else
		philo_is_dead(philo, time_past);
	unlock(philo, fork_first, fork_second);
}
