#ifndef LOGIC_H
# define LOGIC_H

# include "structs/game_state.h"
# include "structs/inputs.h"
# include <math.h>
#include "cub3d.h"
#include "structs/app.h"

# define PLAYER_RAD_PER_FRAME			M_PI * 2. / FPS / 5
# define PLAYER_RAD_PER_MOUSE_PIX		0.0007

void	process_inputs(t_game_state *game_state, t_inputs *inputs);
void	change_state_for_next_frame(t_game_state *game_state);
void	player_trigger_action(t_app *app);

#endif  // LOGIC_H
