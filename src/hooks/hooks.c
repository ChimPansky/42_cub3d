#include "mlx.h"
#include "../cub3d.h"
#include "X11/X.h"

void	set_hooks(t_app *app)
{
	mlx_do_key_autorepeatoff(app->gr.mlx);
	mlx_hook(app->gr.win, KeyPress, KeyPressMask,
		key_press_hook, &app);
	mlx_hook(app->gr.win, KeyRelease, KeyReleaseMask,
		key_release_hook, &app);
}
