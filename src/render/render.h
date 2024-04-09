#ifndef RENDER_H
# define RENDER_H

# include "structs/game_state.h"
# include "structs/minimap.h"
# include "structs/image.h"
# include "structs/app.h"

# define WALL_HEIGHT 0.5
# define FOV M_PI / 3	// 60 degrees player field of view

void	render_minimap(t_minimap *minimap, t_game_state *game_state);
void	render_scene(t_image *scene_image, t_static_graphics *sprites,
		t_game_state *game);

#endif  // RENDER_H
