#ifndef APP_H
# define APP_H

# include "game_state.h"
# include "graphics.h"
# include "inputs.h"
# include "sprites.h"

typedef struct s_app
{
	void			*mlx;
	t_game_state	game_state;
	t_graph			gr;
	t_inputs		inputs;
	t_sprites		sprites;
}		t_app;

int		app_init(t_app *app, char *cub_path);
void	app_destroy(t_app *app);

#endif  // APP_H
