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