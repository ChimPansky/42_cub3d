#ifndef LOGIC_H
# define LOGIC_H

# include "structs/game_state.h"
# include "structs/inputs.h"
# include <math.h>
#include "cub3d.h"

# define PLAYER_SPEED_FIELD_PER_FRAME	1. / FPS
# define PLAYER_RAD_PER_FRAME			M_PI * 2. / FPS

void	process_inputs(t_game_state *game_state, t_inputs *inputs);
void	change_state_for_next_frame(t_game_state *game_state);

#endif  // LOGIC_H
