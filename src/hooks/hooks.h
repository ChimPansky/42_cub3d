#ifndef HOOKS_H
# define HOOKS_H

# include <stdbool.h>

typedef struct s_pressed_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	right;
	bool	left;
}		t_pressed_keys;

typedef struct s_app	t_app;

void	set_hooks(t_app *app);

int		key_release_hook(int key_code, t_app *app);
int		key_press_hook(int key_code, t_app *app);

#endif  // HOOKS_H
