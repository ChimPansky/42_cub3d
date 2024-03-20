#include "render.h"
#include "structs/physics.h"
#include "structs/vector.h"
#include <math.h>

void	render_scene(t_image *scene_image, t_game_state *cub)
{
	t_pvector 	screen_pvect;
	t_pvector	player_pvect;
	t_pos		camera_center;
	t_pos		camera_left;
	t_pos		camera_right;

	player_pvect = pvector(1, cub->player.angle);
	screen_pvect = pvector(1, angles_add(cub->player.angle, M_PI_2));
	camera_center = pos_add_pvec(cub->player.pos, pvector_scale(player_pvect, PLAYER_DISTANCE_FROM_SCREEN));
	camera_left = pos_sub_pvec(camera_center, screen_pvect);
	camera_right = pos_add_pvec(camera_center, screen_pvect);

	(void)screen_pvect;
	(void)scene_image;
	(void)cub;
}
