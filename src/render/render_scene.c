#include "render.h"
#include "structs/app.h"
#include "structs/image.h"
#include "structs/physics.h"
#include "structs/player.h"
#include "structs/trgb.h"
#include "structs/vector.h"
#include "structs/sprites.h"
#include <math.h>

static t_trgb	get_color_from_sprites(t_static_graphics *sprites,
		t_ray_collision collision, double relative_vertical_screen_pos)
{
	//WALL_HEIGHT (=100)

}

static void	draw_screen_column(t_image *screen_img, t_static_graphics *sprites,
	t_pixel *pix, t_ray_collision ray_wall_collision)
{
	int		screen_y;
	t_trgb	color;
	double	wall_dist;

	wall_dist =
	pix->y = 0;
	while (screen_y < screen_img->height)
	{
		color = get_color_from_sprites(sprites, ray_wall_collision,
				(double)screen_y / screen_img->height);
		image_put_pixel(screen_img, *pix, color);
		pix->y++;
	}
}

// beware of negative distance from origin...
static t_ray_collision	get_wall_collision(t_pos pos, t_pvector ray)
{
	t_ray_collision	collision;

	collision.collision_point = pos_create(0.0, 0.0);
	collision.distance_from_origin = pos_distance(pos,
		collision.collision_point);
	(void)pos;
	(void)ray;
	return (collision);
}

// get the left corner of the screen plane by starting from player_position,
// then advancing SCREEN_DIST into direction of player_angle and then turning
// to the left by 90 degrees and advancing by half of the SCREEN_WIDTH:
//	L----SCREEN----R
//	       |
//	       |
//	    PLA YER
static t_pos	get_2d_screen_left_corner(t_player *player)
{
	t_pos	left_corner;

	left_corner = pos_add_pvec(pos_add_pvec(player->pos,
		pvector(SCREEN_DIST, player->angle)),
		pvector(SCREEN_WIDTH / 2, player->angle - M_PI / 2));
	return (left_corner);
}

void	render_scene(t_image *scene_image, t_static_graphics *sprites,
t_game_state *game)
{
	t_pixel			pix;
	t_pos			pos_on_screen;
	t_ray_collision	ray_wall_collision;
	t_pvector		screen_vec;
	t_pvector		ray_vec;

	pix.x = 0;
	screen_vec = pvector(1.0 / scene_image->width, game->player.angle + M_PI / 2);
	pos_on_screen = get_2d_screen_left_corner(&game->player);
	while (pix.x < scene_image->width)
	{
		ray_vec = pvector_from_coords(
			pos_on_screen.x - game->player.pos.x,
			pos_on_screen.y - game->player.pos.y);
		ray_wall_collision = get_wall_collision(pos_on_screen, ray_vec);
		draw_screen_column(scene_image, sprites, &pix, ray_wall_collision);
		pos_on_screen = pos_add_pvec(pos_on_screen, screen_vec);
		pix.x++;
	}
}
