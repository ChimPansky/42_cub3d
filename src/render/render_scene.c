/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:49:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/17 16:08:36 by tkasbari         ###   ########.fr       */
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

void			render_scene(t_image *scene_image, t_static_graphics *sprites,
t_game_state *game);
static void		draw_screen_column(t_image *screen_img,
	t_static_graphics *sprites,	t_pixel  *pixel, t_ray *player_view);
static t_trgb	get_color_from_sprites(t_static_graphics *stat_gr,
		t_ray *ray, t_pixel *pixel, int window_height);

// relative_vertical_screep_pos: ]0.0, 1.0[; 0.0: top of screen, 1.0: bottom]
// wall_height: 0.8
// scaled_wall_height: ]0.0, 0.8[; the further from the wall, the smaller
// fish_eye_remover: make sure that all walls that have the same orthogonal
// distance from the player have the same height on screen
// (even though their actual distance might be further away)
static t_trgb	get_color_from_sprites(t_static_graphics *stat_gr,
		t_ray *ray, t_pixel *pixel, int window_height)
{
	t_image	*wall;
	double	scaled_wall_h;
	double	relative_y;

	relative_y = (double)pixel->y / window_height;

	scaled_wall_h = (1.0 / fmax(ray->vec.r, 1.0)) * WALL_HEIGHT *
		(1.0 / cos(fabs(ray->vec.phi - ray->raycaster.fov_center_angle)));
	if (relative_y < (1.0 - scaled_wall_h) / 2)
	 	return (stat_gr->ceiling_col);
	if (relative_y > scaled_wall_h + (1.0 - scaled_wall_h) / 2)
	 	return (stat_gr->floor_col);
	if (ray->raycaster.sprite_collision == WALL_NO
		|| ray->raycaster.sprite_collision == WALL_SO)
		pixel->x = ray->raycaster.end_point.x - floor(ray->raycaster.end_point.x);
	else
		pixel->x = ray->raycaster.end_point.y - floor(ray->raycaster.end_point.y);
	wall = &stat_gr->sprites.walls[ray->raycaster.sprite_collision - 1];
 	pixel->x *= wall->width;
 	pixel->y = ((relative_y - (1.0 - scaled_wall_h) / 2) / scaled_wall_h)
		* wall->height;
	return (image_get_pixel_color(wall, pixel));
}

static void	draw_screen_column(t_image *screen_img, t_static_graphics *sprites,
	t_pixel *pixel, t_ray *player_view)
{
	t_trgb	color;

 	pixel->y = 0;
	while  (pixel->y < screen_img->height)
	{
		color = get_color_from_sprites(sprites, player_view, pixel, screen_img->height);
		image_put_pixel(screen_img, *pixel, color);
		pixel->y++;
	}
}

void	render_scene(t_image *scene_image, t_static_graphics *sprites,
t_game_state *game)
{
	t_pixel			screen_pixel;
	t_ray			player_view;

	screen_pixel.x = 0;
	screen_pixel.y = 0;
	player_view.origin = game->player.pos;
	player_view.vec = pvector(1.0, game->player.angle - FOV / 2);
	player_view.raycaster.fov_center_angle = game->player.angle;
	while (screen_pixel.x < scene_image->width)
	{
		calculate_ray_collision(&player_view, &game->map);
		draw_screen_column(scene_image, sprites, &screen_pixel, &player_view);
		pvector_rotate(&player_view.vec, FOV / scene_image->width);
		screen_pixel.x++;
	}
}
