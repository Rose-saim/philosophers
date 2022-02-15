#include "philosophers.h"

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
	while (i <= nbr_philo)
	{
		lst_philo = lst_add(lst_philo, i + 1);
		++i;
	}
	return (lst_philo);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}


t_lst_philo	*init_mutex(t_fork *fork, t_lst_philo *lst_philo, int nbr_philo)
{
	int	i;
	t_philo	*head;

	i = 0;
	head = lst_philo->begin;
	fork->tab_fork = malloc(sizeof(pthread_mutex_t) * (nbr_philo + 1));
	if (!fork->tab_fork)
		return (NULL);
	while (i < nbr_philo)
	{
		pthread_mutex_init(&fork->tab_fork[i], NULL);
		++i;
	}
	while (head->id != lst_philo->end->id)
	{
		head->fork = fork;
		head = head->next;
	}
	return (lst_philo);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}