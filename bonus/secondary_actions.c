/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:54:16 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/05 21:16:30 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	too_late(t_philo *philo, long time_past, long tmp)
{
	sem_wait(&philo->sig->is_dead);
	if (tmp >= philo->time_bf_eat
		&& philo->sig->sig_dead == 1)
	{
		philo->sig->sig_dead2 = 2;
		sem_post(&philo->sig->is_dead);
		philo_is_dead(philo, time_past);
		return ;
	}
	sem_post(&philo->sig->is_dead);
}

void	slp(long nbr, t_philo *philo)
{
	long	time_past;
	long	tmp;

	time_past = ft_time();
	tmp = 0;
	while (tmp < nbr && tmp < philo->time_bf_eat
		&& !if_dead(philo))
	{
		if ((nbr - tmp) > 10)
			usleep(10 * 1e3);
		else
		{
			usleep((nbr - tmp) * 1e3);
			break ;
		}
		tmp = ft_time();
		tmp -= time_past;
	}
	too_late(philo, time_past, tmp);
}

void	philo_is_eating(t_philo *philo)
{
	philo->color = "\033[1;33m";
	print_thread(&philo->fork->mutex, "is eating", philo);
	philo->t_beg_lp = ft_time();
	slp(philo->time_for_eat, philo);
	philo->nbr_time_eat -= 1;
}

void	philo_is_dead(t_philo *philo, long time_past)
{
	sem_wait(&philo->sig->is_dead);
	if (philo->sig->sig_dead == 1 || philo->sig->sig_dead2 == 2)
	{
		time_past = time_diff(philo);
		sem_wait(&philo->fork->mutex);
		printf("\033[0;31m%ld %zu died\n", time_past, philo->id);
		sem_post(&philo->fork->mutex);
		philo->sig->sig_dead = 3;
		philo->sig->sig_dead2 = 0;
	}
	sem_post(&philo->sig->is_dead);
}

void	will_eat(t_philo *philo)
{
	long	past_time;

	lock(philo);
	update_signal(philo);
	take_fork(philo);
	past_time = ft_time() - philo->t_beg_lp;
	if (past_time <= philo->time_bf_eat)
		philo_is_eating(philo);
	else
		philo_is_dead(philo, past_time);
	unlock(philo);
}
