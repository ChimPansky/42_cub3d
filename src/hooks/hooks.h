#ifndef HOOKS_H
# define HOOKS_H

# include <stdbool.h>
# include "structs/inputs.h"

void	set_hooks(void *mlx, void *win, t_inputs *inputs);

int		key_release_hook(int key_code, t_inputs *inputs);
int		key_press_hook(int key_code, t_inputs *inputs);

#endif  // HOOKS_H
