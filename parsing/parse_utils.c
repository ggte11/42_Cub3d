#include "../cub3d.h"

int	print_error(char *msg)
{
	static int has_printed;

	if (!has_printed)
	{
		has_printed = 1;
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}

