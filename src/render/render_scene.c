#include "render.h"
#include "structs/vector.h"
#include <math.h>

void	render_scene(t_image *scene_image, t_game_state *cub)
{
	t_pvector screen_pvect;

	screen_pvect = pvector(1, angles_add(cub->player.angle, M_PI_2));

	(void)screen_pvect;
	(void)scene_image;
	(void)cub;
}
