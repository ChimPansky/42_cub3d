#ifndef HOOKS_H
# define HOOKS_H

# include <stdbool.h>
# include "structs/app.h"

void	set_hooks(t_app *app);

int		key_release_hook(int key_code, t_app *app);
int		key_press_hook(int key_code, t_app *app);
int		mouse_motion_hook(int dx, int dy, t_app *app);

#endif  // HOOKS_H
