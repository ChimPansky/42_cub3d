#include "libft.h"

int	print_error(char *err_msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	return (FAILURE);
}
