#include "hooks.h"
#include <X11/keysym.h>
#include <unistd.h>

void	process_tracked_keys(int key_code, t_inputs *inputs, bool is_pressed)
{
	if (key_code == XK_w)
		inputs->w = is_pressed;
	if (key_code == XK_a)
		inputs->a = is_pressed;
	if (key_code == XK_s)
		inputs->s = is_pressed;
	if (key_code == XK_d)
		inputs->d = is_pressed;
	if (key_code == XK_Right)
		inputs->right = is_pressed;
	if (key_code == XK_Left)
		inputs->left = is_pressed;
}

int	key_press_hook(int key_code, t_inputs *inputs)
{
	process_tracked_keys(key_code, inputs, true);
	return (0);
}

// TODO app_destroy on exit, possibly set inputs->esc and check later
#include <stdlib.h>
int	key_release_hook(int key_code, t_inputs *inputs)
{
	if (key_code == XK_Escape)
		exit(0);
	else
		process_tracked_keys(key_code, inputs, false);
	return (0);
}
