#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// can increase factor of DBL_EPSILON to increase tolerance
#define DBL_TOLERANCE (DBL_EPSILON * 1)

void	skip_spaces(char **str);
int		print_error(char *err_msg);
bool	dbl_is_zero(double number);
bool	dbl_is_equal(double a, double b);

#endif  // UTILS_H
