/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:58:38 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/03 14:39:45 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	lock(t_philo *philo, int fork_first, int fork_second)
{
	pthread_mutex_lock(&philo->fork->tab_fork[fork_first]);
	pthread_mutex_lock(&philo->fork->tab_fork[fork_second]);
}

void	unlock(t_philo *philo, int fork_first, int fork_second)
{
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_second]);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_first]);
}

void	print_thread(pthread_mutex_t *l, char *s, t_philo *ph)
{
	long	time_past;

	time_past = (ft_time() - ph->time_begin);
	pthread_mutex_lock(&ph->sig->is_dead);
	pthread_mutex_lock(l);
	if (ph->sig->sig_dead == 1)
	{
		printf("%s%ld %zu", ph->color, time_past, ph->id);
		printf(" %s\n", s);
	}
	pthread_mutex_unlock(l);
	pthread_mutex_unlock(&ph->sig->is_dead);
	return ;
}
