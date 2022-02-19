#include "philosophers.h"

void	write_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(2);
}
void	parsing_argument(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (!av[i])
			write_error("Argument is empty");
		while (av[i][j])
		{
			if (av[i][j] <= '0' && av[i][j] >= '9')
				write_error("Argument is wrong");
			++j;
		}
		++i;
	}
}

void	end_pthread(t_philo * head, size_t id_end)
{
	while (head->id != id_end)
	{
		pthread_join(head->thread_eat, NULL);
		head = head->next;
	}
}
