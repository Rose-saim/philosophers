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
	/* if (philo->id % 2 == 0) */
	/* 	will_eat(philo, philo->id - 1, fork_right); */
	/* else */
	/* 	will_eat(philo, fork_right, philo->id -1); */
}

int	update_signal(t_philo *philo)
{
	pthread_mutex_lock(&philo->sig->change_sig);
	pritf("%d\n", philo->sig->change_sig);	
	if (philo->id % 2 == 0)
	{
		philo->sig->even_max_eat[0] -= 1;
		if (0 >= philo->sig->even_max_eat[0])
		{
			philo->sig->sig_eat = 0;
			philo->sig->even_max_eat[0] = philo->sig->even_max_eat[1];
			pthread_mutex_unlock(&philo->sig->change_sig);
			return (0);
		}
	}
	else
	{
		philo->sig->odd_max_eat[0] -= 1;
		if (0 >= philo->sig->odd_max_eat[0])
		{
			philo->sig->sig_eat = 2;
			philo->sig->odd_max_eat[0] = philo->sig->odd_max_eat[1];
			pthread_mutex_unlock(&philo->sig->change_sig);
			return (0);
		}
	}
	pthread_mutex_unlock(&philo->sig->change_sig);
	return (1);
}


void __eat(t_philo *philo)
{
	int	fork_right;

	fork_right = order_fork(philo);
	lock(philo, fork_right,  philo->id - 1);
	take_fork(philo);
	slp(philo->time_for_eat);
	unlock(philo, fork_right, philo->id - 1);
	if (update_signal(philo) == 0)
		return ;
	puts("END");
	// //sleep
	// print_thread(&philo->fork->mutex, "is sleeping", philo);
	// slp(philo->time_to_sleep);
	//think
	/*print_thread(&philo->fork->mutex, "is thinking", philo);*/
	return ;
}
void	*event_loop(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&philo->sig->change_sig);
		if ((philo->id % 2 == 0 && philo->sig->sig_eat == 2))
		{
			pthread_mutex_unlock(&philo->sig->change_sig);
			__eat(philo);	
		}
		else
			pthread_mutex_unlock(&philo->sig->change_sig);
		/* if ((condition_event(eat, philo)) == 0 */
		/* 	|| philo->nbr_time_eat == 0) */
		/* 	break ; */
		/* if (condition_event(ft_sleep, philo) == 0) */
		/* 	break ; */
		/* if (condition_event(ft_think, philo) == 0) */
		/* 	break ; */
	}
	return (NULL);
}
