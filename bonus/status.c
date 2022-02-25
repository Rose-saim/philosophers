#include "philosophers.h"

void	condition(t_philo *philo, int info, void *f(t_philo *philo, int info))
{
	if (philo->sig->sig_dead == 0)
		return ;
	f(philo, info);
}

void	*lock_fork(t_philo *philo)
{
	float	time_past;

	sem_wait(&philo->fork->tab_fork);
	sem_wait(&philo->fork->tab_fork);
	time_past = time_diff(philo, &philo->time_begin, &philo->time_end);
	philo->color = "\033[0;36m";
	print_thread(&philo->fork->mutex, "has taken forks", philo, time_past);
	return (NULL);
}

void	philo_is_eating(t_philo *philo, int time_past)
{
		philo->color = "\033[1;33m";
		print_thread(&philo->fork->mutex, "is eating", philo, time_past);
		philo->nbr_time_eat -= 1;
}

void	philo_is_dead(t_philo *philo, int time_past)
{
		philo->color = "\033[0;31m";
		print_thread(&philo->fork->mutex, "died", philo, time_past);
		philo->sig->sig_dead = 0;
}

void	take_fork(t_philo *philo)
{
	float	time_past;

	lock_fork(philo);
	usleep((philo->time_for_eat) * 1e3);
	time_past = time_diff(philo, &philo->time_begin, &philo->time_end);
	if (time_past < (philo->time_bf_eat*1e-3))
		philo_is_eating(philo, time_past);
	else
		philo_is_dead(philo, time_past);
	sem_post(&philo->fork->tab_fork);
	sem_post(&philo->fork->tab_fork);
}
