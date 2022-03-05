/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:41:42 by myrmarti          #+#    #+#             */
/*   Updated: 2022/03/04 19:51:17 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_lst_philo *lst_philo)
{
	sem_destroy(&(lst_philo->fork->mutex));
	sem_destroy(&(lst_philo->begin->sig->is_dead));
	sem_destroy(&(lst_philo->begin->sig->change_sig));
	sem_destroy(&(lst_philo->fork->tab_fork));
}

void	end_pthread(t_lst_philo *lst_philo)
{
	int		i;
	t_philo	*head;

	i = 0;
	head = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		pthread_join(head->thread, NULL);
		++i;
		head = head->next;
	}
}

void	free_lst_philo(t_lst_philo *lst_philo)
{
	t_philo	*philo;
	t_philo	*head;

	head = lst_philo->begin;
	philo = head->next;
	free(head);
	while (philo->id != lst_philo->end->id)
	{
		head = philo;
		philo = philo->next;
		free(head);
	}
	free(lst_philo->end);
}

void	free_destroy(t_lst_philo *lst_philo)
{
	end_pthread(lst_philo);
	destroy_mutex(lst_philo);
	free_lst_philo(lst_philo);
}
