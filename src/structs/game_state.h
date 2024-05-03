#ifndef GAME_STATE_H
# define GAME_STATE_H

# include "player.h"
# include "map.h"

typedef struct s_game_state
{
	t_map		map;
	t_player	player;
}			t_game_state;

int		game_init(t_game_state *game_state);
void	game_destroy(t_game_state *game_state);

#endif  // GAME_STATE_H
