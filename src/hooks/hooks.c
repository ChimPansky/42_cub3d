#include "mlx.h"
#include "../cub3d.h"

void	set_hooks(t_app *app)
{
	mlx_hook(app->gr.win, X11_KEY_PRESS, X11_KEY_PRESS_MASK,
		key_press_hook, &app);
	mlx_hook(app->gr.win, X11_KEY_RELEASE, X11_KEY_RELEASE_MASK,
		key_release_hook, &app);
}
