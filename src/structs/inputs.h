#ifndef INPUTS_H
# define INPUTS_H

# include <stdbool.h>

typedef struct s_inputs
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	right;
	bool	left;
	int		mouse_dx;
	int		mouse_dy;
}		t_inputs;

#endif  // INPUTS_H
