#include "app.h"
#include "logic.h"
#include <mlx.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdio.h>

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
	if (key_code == XK_e)
		player_trigger_action(app);
	process_tracked_keys(key_code, &app->inputs, true);
	return (0);
}

static void check_last_inputs(t_app *app)
{
	if (app->inputs.last_inputs[8] == XK_h
		&& app->inputs.last_inputs[4] == XK_s
		&& app->inputs.last_inputs[3] == XK_m
		&& app->inputs.last_inputs[5] == XK_k
		&& app->inputs.last_inputs[7] == XK_u
		&& app->inputs.last_inputs[1] == XK_s
		&& app->inputs.last_inputs[2] == XK_a
		&& app->inputs.last_inputs[6] == XK_l
		&& app->inputs.last_inputs[0] == XK_h)
	{
		app->god_mode = true;
		printf("Cheater!!\n");
	}
}

int	key_release_hook(int key_code, t_app *app)
{
	if (key_code == XK_Escape)
		mlx_loop_end(app->mlx);
	else
		process_tracked_keys(key_code, &app->inputs, false);
	int i = SAVED_INPUTS_CAP - 1;
	while (i--)
		app->inputs.last_inputs[i + 1] = app->inputs.last_inputs[i];
	app->inputs.last_inputs[0] = key_code;
	check_last_inputs(app);
	return (0);
}
