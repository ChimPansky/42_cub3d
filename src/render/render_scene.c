/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:49:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/07 19:39:52 by tkasbari         ###   ########.fr       */
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

// relative_vertical_screep_pos: ]0.0, 1.0[; 0.0: top of screen, 1.0: bottom]
// wall_height: 0.8
// scaled_wall_height: ]0.0, 0.8[; the further from the wall, the smaller
static t_trgb	get_color_from_sprites(t_static_graphics *sprites,
		t_ray_collision collision, double rel_vert_screen_pos)
{
	double	scaled_wall_h;

	scaled_wall_h = (1.0 / fmax(collision.distance_from_origin, 1.0))
						* WALL_HEIGHT;
	if (rel_vert_screen_pos < (1.0 - scaled_wall_h) / 2)
		return (sprites->ceiling_col);
	if (rel_vert_screen_pos > scaled_wall_h + (1.0 - scaled_wall_h) / 2)
		return (sprites->floor_col);
	if (collision.wall_type == WALL_NO)
		return (trgb(0, 255, 0, 0)); // red
	else if (collision.wall_type == WALL_SO)
		return (trgb(0, 0, 255, 0)); // green
	else if (collision.wall_type == WALL_WE)
		return (trgb(0, 0, 0, 255)); // blue
	else
		return (trgb(0, 255, 255, 0)); // yellow
}

static void	draw_screen_column(t_image *screen_img, t_static_graphics *sprites,
	t_pixel *pix, t_ray *player_view)
{
	t_trgb	color;

	pix->y = 0;
	while (pix->y < screen_img->height)
	{
		color = get_color_from_sprites(sprites, player_view->collision,
				(double)pix->y / screen_img->height);
		image_put_pixel(screen_img, *pix, color);
		pix->y++;
	}
}


// static t_ray_collision	get_wall_collision(t_pos pos, t_pvector ray)
// {
// 	t_ray_collision	collision;

// 	collision.collision_point = pos_create(0.0, 0.0);
// 	collision.distance_from_origin = pos_distance(pos,
// 		collision.collision_point);
// 	(void)pos;
// 	(void)ray;
// 	return (collision);
// }

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

	// left_corner = pos_copy(&player->pos);
	// pos_add_pvec(&left_corner, pvector(SCREEN_DIST, player->angle));
	// pos_add_pvec(&left_corner, pvector(SCREEN_WIDTH / 2,
	// 	player->angle - M_PI / 2));
	left_corner = pos_add_pvec(pos_add_pvec(player->pos,
		pvector(SCREEN_DIST, player->angle)),
		pvector(SCREEN_WIDTH / 2, player->angle - M_PI / 2));
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
		calculate_ray_wall_collision(&player_view, &game->map);
		draw_screen_column(scene_image, sprites, &screen_pix, &player_view);
		screen_pos_on_map = pos_add_pvec(screen_pos_on_map, screen_vec);
		//screen_pix.x+=10;	// TODO: remove
		screen_pix.x++;
	}
}
