#include "structs/app.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <unistd.h>
#include "../structs/player.h"

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

int	key_press_hook(int key_code, t_app *app)
{
	process_tracked_keys(key_code, &app->inputs, true);
	return (0);
}

int	key_release_hook(int key_code, t_app *app)
{
	if (key_code == XK_Escape)
		mlx_loop_end(app->mlx);
	else if (key_code == XK_e)
		player_trigger_action(&app->game_state);
	else
		process_tracked_keys(key_code, &app->inputs, false);
	return (0);
}
