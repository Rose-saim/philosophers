#include "philosophers.h"

void	lock_fork(t_philo *philo, int fork)
{
	float	time_past;

	pthread_mutex_lock(&philo->fork->tab_fork[fork]);
	philo->color = "\033[0;36m";
	time_past = time_diff(philo, &philo->time_begin, &philo->time_end);
	print_thread(&philo->fork->mutex, "has taken a fork", philo, time_past);
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

void	take_fork(int	fork_to_take, t_philo *philo)
{
	float	time_past;
	int		fork;

	if (philo->id == philo->last_philo)
		fork = 0;
	else
		fork = fork_to_take + 1;
	lock_fork(philo, fork_to_take);
	lock_fork(philo, fork);
	usleep((philo->time_for_eat) * 1e3);
	time_past = time_diff(philo, &philo->time_begin, &philo->time_end);
	if (time_past < (philo->time_bf_eat*1e-3))
		philo_is_eating(philo, time_past);
	else
		philo_is_dead(philo, time_past);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork]);
	pthread_mutex_unlock(&philo->fork->tab_fork[fork_to_take]);
}
