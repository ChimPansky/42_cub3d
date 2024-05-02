#ifndef INPUTS_H
# define INPUTS_H

# include <stdbool.h>
# define SAVED_INPUTS_CAP 10

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
	int		last_inputs[10];
}		t_inputs;

#endif  // INPUTS_H
