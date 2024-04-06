/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:49:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/06 16:36:52 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "structs/app.h"
#include "structs/image.h"
#include "structs/physics.h"
#include "structs/player.h"
#include "structs/rays.h"
#include "structs/trgb.h"
#include "structs/vector.h"
#include "structs/sprites.h"
#include <math.h>
#include "../ray_casting/ray_casting.h"

static t_trgb	get_color_from_sprites(t_static_graphics *sprites,
		t_ray_collision collision, double relative_vertical_screen_pos)
{
	//WALL_HEIGHT (=100)
	(void)collision;
	(void)relative_vertical_screen_pos;
	return (sprites->floor_col);
}

static void	draw_screen_column(t_image *screen_img, t_static_graphics *sprites,
	t_pixel *pix, t_ray *player_view)
{
	int		screen_y;
	t_trgb	color;
	double	wall_dist;

	wall_dist =
	pix->y = 0;
	while (screen_y < screen_img->height)
	{
		color = get_color_from_sprites(sprites, player_view->collision,
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

	left_corner = pos_copy(&player->pos);
	pos_add_pvec(&left_corner, pvector(SCREEN_DIST, player->angle));
	pos_add_pvec(&left_corner, pvector(SCREEN_WIDTH / 2,
		player->angle - M_PI / 2));
	return (left_corner);
}

// question: calculate distance from player to wall OR from
// screen_pos to wall? for now: from screen_pos
void	render_scene(t_image *scene_image, t_static_graphics *sprites,
t_game_state *game)
{
	t_pixel			screen_pix;
	t_pos			screen_pos_on_map;
	t_ray			player_view;
	t_pvector		screen_vec;

	screen_pix.x = 0;
	screen_vec = pvector(1.0 / scene_image->width, game->player.angle + M_PI / 2);
	screen_pos_on_map = get_2d_screen_left_corner(&game->player);
	while (screen_pix.x < scene_image->width)
	{
		player_view.origin = screen_pos_on_map;
		player_view.direction = pvector_from_coords(
			screen_pos_on_map.x - game->player.pos.x,
			screen_pos_on_map.y - game->player.pos.y);
		ray_calculate_collision(&player_view, &game->map);
		draw_screen_column(scene_image, sprites, &screen_pix, &player_view);
		screen_pos_on_map = pos_add_pvec(screen_pos_on_map, screen_vec);
		screen_pix.x++;
	}
}
