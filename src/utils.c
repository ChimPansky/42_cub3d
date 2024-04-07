#include "utils.h"
#include "libft.h"
#include <float.h>

// can increase factor of DBL_EPSILON to increase tolerance
#define DBL_TOLERANCE (DBL_EPSILON * 1)

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

bool	dbl_is_zero(double number)
{
	return (number > -DBL_TOLERANCE && number < DBL_TOLERANCE);
}

bool	dbl_is_equal(double a, double b)
{
	return (dbl_is_zero(a - b));
}
