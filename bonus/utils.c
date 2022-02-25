#include "philosophers.h"

void	print_thread(sem_t *lock, char *str, t_philo *philo, float time)
{
	if (philo->sig->sig_dead == 0)
		return ;
	sem_wait(lock);
	if (philo->sig->sig_dead == 1)
	{
		printf("%s%f %zu", philo->color, time, philo->id);
		printf(" %s\n", str);
	}
	sem_post(lock);
}

float time_diff(t_philo *philo, struct timeval *start, struct timeval *end)
{
	gettimeofday(&philo->time_end, NULL);
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void    destroy_mutex(t_lst_philo *lst_philo)
{
    int i;

    i = 0;
	sem_destroy(&lst_philo->fork->tab_fork);
	sem_destroy(&lst_philo->fork->mutex);
}

void	end_pthread(t_lst_philo *lst_philo)
{
	int	i = 0;
	t_philo	*head;

	head = lst_philo->begin;
	while (i < lst_philo->nbr_philo)
	{		
		pthread_join(head->thread, NULL);
		head = head->next;
		++i;
	}
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}
