#include "mlx.h"
#include "X11/X.h"
#include "hooks.h"

void	set_hooks(void *mlx, void *win, t_inputs *inputs)
{
	mlx_do_key_autorepeatoff(mlx);
	mlx_hook(win, KeyPress, KeyPressMask,
		key_press_hook, inputs);
	mlx_hook(win, KeyRelease, KeyReleaseMask,
		key_release_hook, inputs);
}
