#include "hooks.h"
#include <X11/keysym.h>
#include <unistd.h>
#include "../cub3d.h"

void	process_tracked_keys(int key_code, t_app *app, bool is_pressed)
{
	if (key_code == XK_W)
		app->pressed_keys.w = is_pressed;
	if (key_code == XK_A)
		app->pressed_keys.a = is_pressed;
	if (key_code == XK_S)
		app->pressed_keys.s = is_pressed;
	if (key_code == XK_D)
		app->pressed_keys.d = is_pressed;
	if (key_code == XK_Right)
		app->pressed_keys.right = is_pressed;
	if (key_code == XK_A)
		app->pressed_keys.left = is_pressed;
}

int	key_press_hook(int key_code, t_app *app)
{
	process_tracked_keys(key_code, app, true);
	return (0);
}

int	key_release_hook(int key_code, t_app *app)
{
	if (key_code == XK_Escape)
		exit(0);
	else
		process_tracked_keys(key_code, app, false);
	return (0);
}
