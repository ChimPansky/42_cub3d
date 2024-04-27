#include "mlx.h"
#include "X11/X.h"
#include "hooks.h"

void	set_hooks(t_app *app)
{
	mlx_hook(app->gr.win, KeyPress, KeyPressMask,
		key_press_hook, app);
	mlx_hook(app->gr.win, KeyRelease, KeyReleaseMask,
		key_release_hook, app);
	mlx_hook(app->gr.win, MotionNotify, PointerMotionMask,
		mouse_motion_hook, app);
	mlx_hook(app->gr.win, DestroyNotify, SubstructureNotifyMask,
		mlx_loop_end, app->mlx);
}

int	mouse_motion_hook(int x, int y, t_app *app)
{
	const int	center_x = app->gr.scene.width / 2;
	const int	center_y = app->gr.scene.height / 2;

	app->inputs.mouse_dx += x - center_x;
	app->inputs.mouse_dy += y - center_y;
	mlx_mouse_move(app->mlx, app->gr.win, center_x, center_y);
	return (0);
}
