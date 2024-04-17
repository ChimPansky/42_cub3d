/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:49:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/17 10:39:26 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "structs/app.h"
#include "structs/image.h"
#include "structs/physics.h"
#include "structs/player.h"
#include "structs/trgb.h"
#include "vector/vector.h"
#include "structs/sprites.h"
#include <math.h>
#include "structs/ray.h"


static	t_trgb	get_color_from_wall(t_image *wall, double rel_x, double rel_y)
{
	t_pixel	pix;

	pix.x = rel_x * wall->width;
	pix.y = rel_y * wall->height;
	return (image_get_pixel_color(wall, &pix));
}

// relative_vertical_screep_pos: ]0.0, 1.0[; 0.0: top of screen, 1.0: bottom]
// wall_height: 0.8
// scaled_wall_height: ]0.0, 0.8[; the further from the wall, the smaller
// fish_eye_remover: make sure that all walls that have the same orthogonal
// distance from the player have the same height on screen
// (even though their actual distance might be further away)
static t_trgb	get_color_from_sprites(t_static_graphics *stat_gr,
		t_ray *ray, double rel_vert_screen_pos)
{
	double	scaled_wall_h;
	double	fish_eye_remover;
	double	rel_x;

	fish_eye_remover = 1.0 / cos(fabs(ray->vec.phi - ray->rc.fov_center_angle));
	scaled_wall_h = (1.0 / fmax(ray->vec.r, 1.0))
					* WALL_HEIGHT * fish_eye_remover;
	 if (rel_vert_screen_pos < (1.0 - scaled_wall_h) / 2)
	 	return (stat_gr->ceiling_col);
	 if (rel_vert_screen_pos > scaled_wall_h + (1.0 - scaled_wall_h) / 2)
	 	return (stat_gr->floor_col);

	if (ray->rc.sprite_collision == WALL_NO || ray->rc.sprite_collision == WALL_SO)
		rel_x = ray->rc.end_point.x - floor(ray->rc.end_point.x);
	else
		rel_x = ray->rc.end_point.y - floor(ray->rc.end_point.y);
	return (get_color_from_wall(
			&stat_gr->sprites.walls[ray->rc.sprite_collision - 1],
			rel_x,
			(rel_vert_screen_pos - (1.0 - scaled_wall_h) / 2) / scaled_wall_h));
}

static void	draw_screen_column(t_image *screen_img, t_static_graphics *sprites,
	t_pixel *pix, t_ray *player_view)
{
	t_trgb	color;

	pix->y = 0;
	while (pix->y < screen_img->height)
	{
		color = get_color_from_sprites(sprites, player_view,
				(double)pix->y / screen_img->height);
		image_put_pixel(screen_img, *pix, color);
		pix->y++;
	}
}

void	render_scene(t_image *scene_image, t_static_graphics *sprites,
t_game_state *game)
{
	t_pixel			screen_pix;
	t_ray			player_view;

	screen_pix.x = 0;
	player_view.origin = game->player.pos;
	player_view.vec = pvector(1.0, game->player.angle - FOV / 2);
	player_view.rc.fov_center_angle = game->player.angle;
	while (screen_pix.x < scene_image->width)
	{
		calculate_ray_wall_collision(&player_view, &game->map);

		draw_screen_column(scene_image, sprites, &screen_pix, &player_view);
		pvector_rotate(&player_view.vec, FOV / scene_image->width);
		screen_pix.x++;
	}
}
