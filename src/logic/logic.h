#ifndef LOGIC_H
# define LOGIC_H

# include "structs/game_state.h"
# include "structs/inputs.h"

# define PLAYER_SPEED_FIELD_PER_FRAME 0.05

void	process_inputs(t_game_state *game_state, t_inputs *inputs);
void	change_state_for_next_frame(t_game_state *game_state);

#endif  // LOGIC_H
