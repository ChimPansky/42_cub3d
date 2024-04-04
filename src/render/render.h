#ifndef RENDER_H
# define RENDER_H

# include "structs/game_state.h"
# include "structs/minimap.h"
# include "structs/image.h"
# include "structs/app.h"

# define SCREEN_DIST 1.0
# define SCREEN_WIDTH 2.0
# define WALL_HEIGHT 100

void	render_minimap(t_minimap *minimap, t_game_state *game_state);
void	render_scene(t_image *scene_image, t_static_graphics *sprites,
		t_game_state *game);

#endif  // RENDER_H
