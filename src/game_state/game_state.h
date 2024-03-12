#ifndef GAME_STATE_H
# define GAME_STATE_H

# include "../cub3d.h"

int		game_init(t_game_state *game);
void	game_destroy(t_game_state *game);
void	process_logic(t_app *app);

#endif  // GAME_STATE_H
