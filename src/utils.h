#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// can increase factor of DBL_EPSILON to increase tolerance

void	skip_spaces(char **str);
int		print_error(char *err_msg);
bool	dbl_is_almost_zero(double a);

#endif  // UTILS_H
