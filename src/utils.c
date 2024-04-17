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
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		ft_dprintf(STDERR_FILENO, "Unknown Error\n");
	return (FAILURE);
}

bool	dbl_is_almost_zero(double a)
{
	if (a == 0)
		return (true);
	if (a < 0 && a > -10e-10)
		return (true);
	if (a > 0 && a < 10e-10)
		return (true);
	return (false);
}
