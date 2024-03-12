#ifndef GAME_H
# define GAME_H

typedef struct s_game_state t_game_state;

int 	game_init(t_game_state *game);
void	game_destroy(t_game_state *game);

#endif  // GAME_H
