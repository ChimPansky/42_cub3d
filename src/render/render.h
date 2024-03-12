#ifndef RENDER_H
# define RENDER_H

# include "../cub3d.h"
# include "../graphics/mlx_utils.h"

typedef struct s_pixel
{
	int	x;
	int	y;
}		t_pixel;

void	render_minimap(t_image *mm_image, t_game_state *game);
void	render_scene(t_image *scene_image, t_game_state *game);

#endif  // RENDER_H
