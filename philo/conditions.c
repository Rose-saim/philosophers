/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:42:46 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/05 14:44:27 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->sig->is_dead);
	if (philo->sig->sig_dead == 3)
	{
		pthread_mutex_unlock(&philo->sig->is_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->sig->is_dead);
	return (0);
}

int	condition_event(void (*f)(t_philo*), t_philo *philo)
{
	if (if_dead(philo) == 1)
		return (0);
	(*f)(philo);
	return (1);
}

int	order_fork(t_philo *philo)
{
	int	fork_right;

	if (philo->id == philo->last_philo)
		fork_right = 0;
	else
		fork_right = philo->id;
	return (fork_right);
}
