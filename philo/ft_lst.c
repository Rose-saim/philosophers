#include "philosophers.h"

void	add_info_lst(t_lst_philo *lst_philo, int info[])
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{
		gettimeofday(&philo->time_begin, NULL);
		philo->last_philo = lst_philo->end->id;
		philo->time_bf_eat = info[0];
		philo->time_for_eat = info[1];
		philo->time_to_sleep = info[2];
		philo->nbr_time_eat = info[3];
		philo->lst_philo = lst_philo;
		philo = philo->next;
		++i;
	}
}

t_lst_philo	*lst_add(t_lst_philo *lst_philo, int i)
{
	t_philo	*node;
	t_philo	*head;

	if (!lst_philo->begin)
	{
		node = (t_philo *)malloc(sizeof(t_philo));
		if (!node)
			return (NULL);
		node->id = (size_t)i;
		node->next = node;
		lst_philo->begin = node;
		lst_philo->end = node;
	}
	else
	{
		head = lst_philo->begin;
		node = malloc(sizeof(t_philo));
		if (!node)
			return (NULL);
		node->id = i;
		node->next = lst_philo->begin;
		lst_philo->end->next = node;
		lst_philo->end = node;
	}
	return (lst_philo);
}

t_lst_philo	*creat_lst(t_lst_philo *lst_philo, int nbr_philo)
{
	int			i;

	i = 0;
	lst_philo->begin = NULL;
	lst_philo->end = NULL;
	while (i < nbr_philo)
	{
		lst_philo = lst_add(lst_philo, i + 1);
		++i;
	}
	return (lst_philo);
}

void	free_lst_philo(t_lst_philo *lst_philo)
{
    t_philo *philo;
    t_philo *head;

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