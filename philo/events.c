#include "philosophers.h"

void	*ft_sleep(t_philo *philo)
{
	float	time_past;

	usleep(philo->time_to_sleep*1e3);
	time_past = time_diff(philo, &philo->time_begin, &philo->time_end);
	philo->color = "\033[0;32m";
	print_thread(&philo->fork->mutex, "is sleeping", philo, time_past);
	return (NULL);
}

void	*ft_think(t_philo *philo)
{
	float	time_past;
	
	time_past = time_diff(philo, &philo->time_begin, &philo->time_end);
	philo->color = "\033[0;37m";
	print_thread(&philo->fork->mutex, "is thinking", philo, time_past);
	return (NULL);
}
void	*eat(t_philo *philo)
{
	static	int i = 0;

	if ((philo->id % 2) == i)
	{
		usleep(philo->time_for_eat * 1e1);
		if (i == 0)
			i = 1;
		else
			i = 0;
	}
	take_fork(philo->id - 1, philo);
	return(NULL);
}

void	*event_loop(void *p)
{
	
	t_philo *philo;
	
	philo = (t_philo *)p;
	philo->sig->sig_dead = 1;
	while (1)
	{
		eat(philo);
		if (philo->nbr_time_eat == 0 || philo->sig->sig_dead == 0)
			break ;
		gettimeofday(&philo->time_begin, NULL);
		ft_sleep(philo);
		if (philo->sig->sig_dead == 0)
			break ;
		ft_think(philo);
		if (philo->sig->sig_dead == 0)
			break ;
	}
	return (NULL);
}
