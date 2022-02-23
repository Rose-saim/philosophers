#include "philosophers.h"

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
	(void)lst_philo;
	fork->tab_fork = malloc(sizeof(pthread_mutex_t) * (nbr_philo + 1));
	if (!fork->tab_fork)
		return (NULL);
	pthread_mutex_init(&(fork->mutex), NULL);
	while (i < nbr_philo)
	{
		pthread_mutex_init(&(fork->tab_fork[i]), NULL);
		++i;
	}
	(lst_philo->fork) = fork;
	i = 0;
	while (i < lst_philo->nbr_philo)
	{
		head->fork = fork;
		head = head->next;
		++i;
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
