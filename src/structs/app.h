#ifndef APP_H
# define APP_H

# include "game_state.h"
# include "graphics.h"
# include "inputs.h"

typedef struct s_app
{
	void			*mlx;
	t_game_state	game_state;
	t_graph			gr;
	t_inputs		inputs;
}		t_app;

#endif  // APP_H
