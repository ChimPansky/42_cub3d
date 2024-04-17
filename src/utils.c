#include "utils.h"
#include "libft.h"
#include <float.h>

void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

int	print_error(char *err_msg)
{
	// ft_dprintf(STDERR_FILENO, COLOR_RED);
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		ft_dprintf(STDERR_FILENO, "Unknown Error\n");
	// ft_dprintf(STDERR_FILENO, COLOR_RESET);
	return (FAILURE);
}

bool	dbl_is_almost_zero(double a)
{
	return (a < 10e-10);
}
