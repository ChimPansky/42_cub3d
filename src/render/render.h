#ifndef RENDER_H
# define RENDER_H

# include "structs/game_state.h"
# include "structs/minimap.h"

typedef struct s_pixel
{
	int	x;
	int	y;
}		t_pixel;

void	render_minimap(t_minimap *minimap, t_game_state *game_state);
void	render_scene(t_image *scene_image, t_game_state *game_state);

#endif  // RENDER_H
