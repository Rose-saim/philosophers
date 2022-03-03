/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:58:38 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/03 13:05:57 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock(t_philo *philo)
{
	sem_wait(&philo->fork->tab_fork);
	sem_wait(&philo->fork->tab_fork);
}

void	unlock(t_philo *philo)
{
	sem_post(&philo->fork->tab_fork);
	sem_post(&philo->fork->tab_fork);
}

void	print_thread(sem_t *l, char *s, t_philo *ph)
{
	long	time_past;

	time_past = ft_time() - ph->time_begin;
	sem_wait(&ph->sig->is_dead);
	sem_wait(l);
	if (ph->sig->sig_dead == 1)
	{
		printf("%s%ld %zu", ph->color, time_past, ph->id);
		printf(" %s\n", s);
	}
	sem_post(l);
	sem_post(&ph->sig->is_dead);
	return ;
}
